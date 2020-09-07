#include "tree-sitter/tree-sitter.hpp"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <tree_sitter/api.h>
#include <utility>
#include <vector>

namespace ts {

// struct Point
bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.row == rhs.row && lhs.column == rhs.column;
}
bool operator!=(const Point& lhs, const Point& rhs) { return !(lhs == rhs); }
std::ostream& operator<<(std::ostream& o, const Point& self) {
    return o << "Point{ .row = " << self.row << ", .column = " << self.column << "}";
}

// struct Location
bool operator==(const Location& lhs, const Location& rhs) {
    return lhs.point == rhs.point && lhs.byte == rhs.byte;
}
bool operator!=(const Location& lhs, const Location& rhs) { return !(lhs == rhs); }
std::ostream& operator<<(std::ostream& o, const Location& self) {
    return o << "Location{ .point = " << self.point << ", .byte = " << self.byte << "}";
}

// struct Range
bool operator==(const Range& lhs, const Range& rhs) {
    return lhs.start == rhs.start && lhs.end == rhs.end;
}
bool operator!=(const Range& lhs, const Range& rhs) { return !(lhs == rhs); }
std::ostream& operator<<(std::ostream& o, const Range& self) {
    return o << "Range{ .start = " << self.start << ", .end = " << self.end << "}";
}

// struct Edit
bool operator==(const Edit& lhs, const Edit& rhs) {
    return lhs.range == rhs.range && lhs.replacement == rhs.replacement;
}
bool operator!=(const Edit& lhs, const Edit& rhs) { return !(lhs == rhs); }
std::ostream& operator<<(std::ostream& o, const Edit& self) {
    return o << "Edit{ .range = " << self.range << ", .replacement = " << self.replacement << "}";
}

// class Language
Language::Language(const TSLanguage* lang) noexcept : lang(lang) {}

const TSLanguage* Language::raw() const { return this->lang; }

std::uint32_t Language::node_type_count() const { return ts_language_symbol_count(this->raw()); }

const char* Language::node_type_name(TypeId type_id) const {
    return ts_language_symbol_name(this->raw(), type_id);
}

TypeId Language::node_type_id(std::string_view name, bool is_named) const {
    return ts_language_symbol_for_name(this->raw(), name.data(), name.size(), is_named);
}

std::uint32_t Language::field_count() const { return ts_language_field_count(this->raw()); }

const char* Language::field_name(FieldId field_id) const {
    return ts_language_field_name_for_id(this->raw(), field_id);
}

FieldId Language::field_id(std::string_view name) const {
    return ts_language_field_id_for_name(this->raw(), name.data(), name.size());
}

TypeKind Language::node_type_kind(TypeId type_id) const {
    switch (ts_language_symbol_type(this->raw(), type_id)) {
    case TSSymbolTypeRegular:
        return TypeKind::Named;
    case TSSymbolTypeAnonymous:
        return TypeKind::Anonymous;
    case TSSymbolTypeAuxiliary:
        return TypeKind::Hidden;
    }
}

std::uint32_t Language::version() const { return ts_language_version(this->raw()); }

bool language_compatible(const Language& lang) {
    return lang.version() >= TREE_SITTER_MIN_VERSION && lang.version() <= TREE_SITTER_VERSION;
}

// class Node
Node::Node(TSNode node, const Tree& tree) noexcept : node(node), tree_(&tree) {}

TSNode Node::raw() const { return this->node; }
const Tree& Node::tree() const { return *this->tree_; }

bool Node::is_null() const { return ts_node_is_null(this->node); }
bool Node::is_named() const { return ts_node_is_named(this->node); }
bool Node::is_missing() const { return ts_node_is_missing(this->node); }
bool Node::is_extra() const { return ts_node_is_extra(this->node); }
bool Node::has_changes() const { return ts_node_has_changes(this->node); }
bool Node::has_error() const { return ts_node_has_error(this->node); }

const char* Node::type() const { return ts_node_type(this->node); }
TypeId Node::type_id() const { return ts_node_symbol(this->node); }

Node Node::parent() const { return Node(ts_node_parent(this->node), this->tree()); }

std::uint32_t Node::child_count() const { return ts_node_child_count(this->node); }

Node Node::child(std::uint32_t index) const {
    return Node(ts_node_child(this->node, index), this->tree());
}

std::vector<Node> Node::children() const {
    std::uint32_t num_children = this->child_count();

    std::vector<Node> children;
    children.reserve(num_children);
    for (std::uint32_t index = 0; index < num_children; ++index) {
        children.push_back(this->child(index));
    }

    return children;
}

std::uint32_t Node::named_child_count() const { return ts_node_named_child_count(this->node); }

Node Node::named_child(std::uint32_t index) const {
    return Node(ts_node_named_child(this->node, index), this->tree());
}

std::vector<Node> Node::named_children() const {
    std::uint32_t num_children = this->named_child_count();

    std::vector<Node> children;
    children.reserve(num_children);
    for (std::uint32_t index = 0; index < num_children; ++index) {
        children.push_back(this->named_child(index));
    }

    return children;
}

Node Node::next_sibling() const { return Node(ts_node_next_sibling(this->node), this->tree()); }
Node Node::prev_sibling() const { return Node(ts_node_prev_sibling(this->node), this->tree()); }
Node Node::next_named_sibling() const {
    return Node(ts_node_next_named_sibling(this->node), this->tree());
}
Node Node::prev_named_sibling() const {
    return Node(ts_node_prev_named_sibling(this->node), this->tree());
}

std::uint32_t Node::start_byte() const { return ts_node_start_byte(this->node); }
std::uint32_t Node::end_byte() const { return ts_node_end_byte(this->node); }

Point Node::start_point() const {
    TSPoint point = ts_node_start_point(this->node);
    return {.row = point.row, .column = point.column};
}
Point Node::end_point() const {
    TSPoint point = ts_node_end_point(this->node);
    return {.row = point.row, .column = point.column};
}

Location Node::start() const {
    return Location{
        .point = this->start_point(),
        .byte = this->start_byte(),
    };
}
Location Node::end() const {
    return Location{
        .point = this->end_point(),
        .byte = this->end_byte(),
    };
}

Range Node::range() const {
    return Range{
        .start = this->start(),
        .end = this->end(),
    };
}

std::string Node::text() const {
    auto start = this->start_byte();
    auto count = this->end_byte() - start;
    return this->tree().source().substr(start, count);
}

std::string Node::as_s_expr() const {
    std::unique_ptr<char, decltype(&free)> raw_string{ts_node_string(this->node), free};
    if (raw_string == nullptr) {
        return std::string();
    } else {
        return std::string(raw_string.get());
    }
}

bool operator==(const Node& lhs, const Node& rhs) {
    // was created from the same tree and nodes are equal
    return ts_node_eq(lhs.raw(), rhs.raw());
}
bool operator!=(const Node& lhs, const Node& rhs) { return !(lhs == rhs); }

std::ostream& operator<<(std::ostream& os, const Node& node) { return os << node.as_s_expr(); }

// class Tree
Tree::Tree(TSTree* tree, std::string source, Parser& parser)
    : tree(tree, ts_tree_delete), source_(std::move(source)), parser(&parser) {}

Tree::Tree(const Tree& other)
    : tree(ts_tree_copy(other.raw()), ts_tree_delete), source_(other.source()),
      parser(other.parser) {}
Tree& Tree::operator=(const Tree& other) {
    Tree copy{other};
    swap(copy, *this);
    return *this;
}

void swap(Tree& self, Tree& other) noexcept {
    using std::swap;
    swap(self.tree, other.tree);
    swap(self.source_, other.source_);
    swap(self.parser, other.parser);
}

const TSTree* Tree::raw() const { return this->tree.get(); }

const std::string& Tree::source() const { return this->source_; }

Node Tree::root_node() const { return Node(ts_tree_root_node(this->raw()), *this); }

Language Tree::language() const { return Language(ts_tree_language(this->raw())); }

// helper function to apply one edit to the tree and source code
static void _apply_edit(const Edit& edit, TSTree* tree, std::string& source) {
    std::uint32_t old_size = edit.range.end.byte - edit.range.start.byte;

    source.replace(edit.range.start.byte, old_size, edit.replacement);

    std::uint32_t size_diff = old_size - static_cast<std::uint32_t>(edit.replacement.size());

    TSInputEdit input_edit{
        .start_byte = edit.range.start.byte,
        .old_end_byte = edit.range.end.byte,
        .new_end_byte = edit.range.end.byte + size_diff,
        .start_point =
            TSPoint{
                .row = edit.range.start.point.row,
                .column = edit.range.start.point.column,
            },
        .old_end_point =
            TSPoint{
                .row = edit.range.end.point.row,
                .column = edit.range.end.point.column,
            },
        .new_end_point =
            TSPoint{
                .row = edit.range.end.point.row,
                .column = edit.range.end.point.column + size_diff,
            },
    };

    ts_tree_edit(tree, &input_edit);
}

static inline Point _point(const TSPoint& point) {
    return Point{
        .row = point.row,
        .column = point.column,
    };
}

static inline Location _location(const TSPoint& point, const std::uint32_t byte) {
    return Location{
        .point = _point(point),
        .byte = byte,
    };
}

static inline Range _range(const TSRange& range) {
    return Range{
        .start = _location(range.start_point, range.start_byte),
        .end = _location(range.end_point, range.end_byte),
    };
}

static std::vector<Range> _get_changed_ranges(const TSTree* old_tree, const TSTree* new_tree) {
    std::uint32_t length;

    std::unique_ptr<TSRange, decltype(&free)> ranges{
        ts_tree_get_changed_ranges(old_tree, new_tree, &length), free};

    if (length == 0) {
        return {};
    }

    const TSRange* begin = ranges.get();
    const TSRange* end = begin + static_cast<std::size_t>(length);

    std::vector<Range> changed_ranges{length};

    std::transform(begin, end, changed_ranges.begin(),
                   [](const TSRange& range) { return _range(range); });

    return changed_ranges;
}

std::vector<Range> Tree::edit(std::vector<Edit> edits) {
    // save copies of the previous values so we can return the old syntax tree
    std::string new_source = this->source();
    std::unique_ptr<TSTree, void (*)(TSTree*)> old_tree = std::move(this->tree);

    // Sort edits so the edits that are at the end of the source code are applied
    // before the edits that are at the beginning.
    // This prevents conflicts in (the common) case that the source locations
    // has a different size after the edit (and therefore move everything
    // after them in the string).
    // Note: This assumes that the edits are not overlapping or duplicate
    std::sort(edits.begin(), edits.end(), [](const Edit& edit1, const Edit& edit2) {
        return edit1.range.start.byte > edit2.range.start.byte;
    });

    for (const auto& edit : edits) {
        _apply_edit(edit, old_tree.get(), new_source);
    }

    // reparse the source code
    Tree new_tree = this->parser->parse_string(old_tree.get(), std::move(new_source));

    // update this tree
    swap(*this, new_tree);

    std::vector<Range> changed_ranges = _get_changed_ranges(old_tree.get(), this->raw());

    return changed_ranges;
}

void Tree::print_dot_graph(std::string_view file) const {
    std::unique_ptr<std::FILE, decltype(&fclose)> f{std::fopen(file.data(), "w"), fclose};
    ts_tree_print_dot_graph(this->raw(), f.get());
}

// class Cursor
Cursor::Cursor(Node node) noexcept : cursor(ts_tree_cursor_new(node.raw())), tree(&node.tree()) {}
Cursor::Cursor(const Tree& tree) noexcept : Cursor(tree.root_node()) {}
Cursor::~Cursor() noexcept { ts_tree_cursor_delete(&this->cursor); }
Cursor::Cursor(const Cursor& cursor) noexcept
    : cursor(ts_tree_cursor_copy(&cursor.cursor)), tree(cursor.tree) {}

Cursor& Cursor::operator=(const Cursor& other) noexcept {
    Cursor copy{other};
    swap(copy, *this);
    return *this;
}

void swap(Cursor& self, Cursor& other) noexcept {
    using std::swap;
    swap(self.cursor, other.cursor);
    swap(self.tree, other.tree);
}

void Cursor::reset(Node node) { ts_tree_cursor_reset(&this->cursor, node.raw()); }
void Cursor::reset(const Tree& tree) {
    ts_tree_cursor_reset(&this->cursor, tree.root_node().raw());
}

Node Cursor::current_node() const {
    return Node(ts_tree_cursor_current_node(&this->cursor), *this->tree);
}
const char* Cursor::current_field_name() const {
    return ts_tree_cursor_current_field_name(&this->cursor);
}
FieldId Cursor::current_field_id() const { return ts_tree_cursor_current_field_id(&this->cursor); }

bool Cursor::goto_parent() { return ts_tree_cursor_goto_parent(&this->cursor); }
bool Cursor::goto_first_child() { return ts_tree_cursor_goto_first_child(&this->cursor); }
bool Cursor::goto_next_sibling() { return ts_tree_cursor_goto_next_sibling(&this->cursor); }
bool Cursor::goto_first_named_child() {
    if (!this->goto_first_child()) {
        return false;
    }

    // walk over siblings until we encounter a named node
    while (!this->current_node().is_named()) {
        if (!this->goto_next_sibling()) {
            return false;
        }
    }
    return true;
}
bool Cursor::goto_next_named_sibling() {
    // walk over siblings until we encounter a named node
    do {
        if (!this->goto_next_sibling()) {
            return false;
        }
    } while (!this->current_node().is_named());
    return true;
}

std::vector<Node> Cursor::children() {
    std::vector<Node> children;

    if (!this->goto_first_child()) {
        return children;
    }

    children.push_back(this->current_node());

    while (this->goto_next_sibling()) {
        children.push_back(this->current_node());
    }

    return children;
}

std::vector<Node> Cursor::named_children() {
    std::vector<Node> children;

    if (!this->goto_first_named_child()) {
        return children;
    }

    children.push_back(this->current_node());

    while (this->goto_next_named_sibling()) {
        children.push_back(this->current_node());
    }

    return children;
}

// class Parser
Parser::Parser() : Parser(LUA_LANGUAGE) {}
Parser::Parser(const Language& lang) : parser(ts_parser_new(), ts_parser_delete) {
    if (!ts_parser_set_language(this->parser.get(), lang.raw())) {
        // only occurs when version of lua parser and tree-sitter library
        // are incompatible
        // see: ts_language_version, TREE_SITTER_LANGUAGE_VERSION,
        // TREE_SITTER_MIN_COMPATIBLE_LANGUAGE_VERSION
        throw std::runtime_error("failed to set language on tree-sitter parser");
    }
}

TSParser* Parser::raw() const { return this->parser.get(); }

Language Parser::language() const { return Language(ts_parser_language(this->raw())); }

Tree Parser::parse_string(const TSTree* old_tree, std::string source) {
    TSTree* tree = ts_parser_parse_string(this->raw(), old_tree, source.c_str(), source.length());
    if (tree == nullptr) {
        // TL;DR this should never happen
        // This can occur when:
        // - there is no language set (should not happen because we manage that)
        // - or the timeout was reached (see ts_parser_set_timeout_micros)
        // - or the parsing was cancelled using ts_parser_set_cancellation_flag
        // In the latter two cases the parser could be restarted by calling it
        // with the same arguments. But these cases also can't happen because
        // we don't allow setting those flags.
        throw std::runtime_error("failed to parse");
    }
    return Tree(tree, std::move(source), *this);
}
Tree Parser::parse_string(std::string str) { return parse_string(nullptr, std::move(str)); }

// class Query
static TSQuery* _make_query(std::string_view source) {
    std::uint32_t error_offset;
    TSQueryError error_type;
    TSQuery* query = ts_query_new(LUA_LANGUAGE.raw(), source.data(), source.length(), &error_offset,
                                  &error_type);

    if (query == nullptr) {
        std::string error_type_str;
        switch (error_type) {
        case TSQueryErrorSyntax:
            error_type_str = "syntax";
            break;
        case TSQueryErrorNodeType:
            error_type_str = "node type";
            break;
        case TSQueryErrorField:
            error_type_str = "field";
            break;
        case TSQueryErrorCapture:
            error_type_str = "capture";
            break;
        case TSQueryErrorNone:
        default:
            error_type_str = "unknown";
            break;
        }
        // TODO custom exception
        throw std::runtime_error("failed to create query: " + error_type_str +
                                 " error at position " + std::to_string(error_offset));
    }

    return query;
}

Query::Query(std::string_view source) : query(_make_query(source), ts_query_delete) {}

void swap(Query& self, Query& other) noexcept { std::swap(self.query, other.query); }

const TSQuery* Query::raw() const { return this->query.get(); }
TSQuery* Query::raw() { return this->query.get(); }

std::uint32_t Query::pattern_count() const { return ts_query_pattern_count(this->raw()); }
std::uint32_t Query::capture_count() const { return ts_query_capture_count(this->raw()); }
std::uint32_t Query::string_count() const { return ts_query_string_count(this->raw()); }

std::uint32_t Query::start_byte_for_pattern(std::uint32_t id) const {
    return ts_query_start_byte_for_pattern(this->raw(), id);
}

std::string_view Query::capture_name_for_id(std::uint32_t id) const {
    std::uint32_t length = 0;
    const char* name = ts_query_capture_name_for_id(this->raw(), id, &length);
    return std::string_view(name, length);
}
std::string_view Query::string_value_for_id(std::uint32_t id) const {
    std::uint32_t length;
    const char* value = ts_query_string_value_for_id(this->raw(), id, &length);
    return std::string_view(value, length);
}

void Query::disable_capture(std::string_view name) {
    ts_query_disable_capture(this->raw(), name.data(), name.length());
}
void Query::disable_pattern(std::uint32_t id) { ts_query_disable_pattern(this->raw(), id); }

// struct Capture
Capture::Capture(TSQueryCapture capture, const Tree& tree) noexcept
    : node(Node(capture.node, tree)), index(capture.index) {}

std::ostream& operator<<(std::ostream& os, const Capture& capture) {
    return os << "Capture { .node = " << capture.node << ", .index = " << capture.index << " }";
}
std::ostream& operator<<(std::ostream& os, const std::vector<Capture>& captures) {
    os << "[ ";
    const char* sep = "";
    for (const auto& capture : captures) {
        os << sep << capture;
        sep = ", ";
    }
    os << " ]";
    return os;
}

// struct Match
Match::Match(TSQueryMatch match, const Tree& tree) noexcept
    : id(match.id), pattern_index(match.pattern_index) {
    const TSQueryCapture* start = match.captures;
    const TSQueryCapture* end = start + match.capture_count;
    const std::size_t size = end - start;

    this->captures.reserve(size);
    std::transform(start, end, std::back_inserter(this->captures),
                   [&tree](const TSQueryCapture capture) { return Capture(capture, tree); });
}

std::optional<Capture> Match::capture_with_index(std::uint32_t index) const {
    for (const auto& capture : this->captures) {
        if (capture.index == index) {
            return capture;
        }
    }
    return std::nullopt;
}

std::ostream& operator<<(std::ostream& os, const Match& match) {
    return os << "Match { .id = " << match.id << ", .pattern_index = " << match.pattern_index
              << ", .captures = " << match.captures.size() << " }";
}
std::ostream& operator<<(std::ostream& os, const std::vector<Match>& matches) {
    os << "[ ";
    const char* sep = "";
    for (const auto& match : matches) {
        os << sep << match;
        sep = ", ";
    }
    os << " ]";
    return os;
}

// class QueryCursor
QueryCursor::QueryCursor(const Tree& tree) noexcept
    : cursor(ts_query_cursor_new(), ts_query_cursor_delete), tree(&tree) {}

const TSQueryCursor* QueryCursor::raw() const { return this->cursor.get(); }
TSQueryCursor* QueryCursor::raw() { return this->cursor.get(); }

void QueryCursor::exec(const Query& query, Node node) {
    ts_query_cursor_exec(this->raw(), query.raw(), node.raw());
}

void QueryCursor::exec(const Query& query) {
    ts_query_cursor_exec(this->raw(), query.raw(), this->tree->root_node().raw());
}

std::optional<Match> QueryCursor::next_match() {
    TSQueryMatch match;
    if (ts_query_cursor_next_match(this->raw(), &match)) {
        return Match(match, *this->tree);
    } else {
        return std::nullopt;
    }
}

std::optional<Capture> QueryCursor::next_capture() {
    TSQueryMatch raw_match;
    std::uint32_t index;
    if (ts_query_cursor_next_capture(this->raw(), &raw_match, &index)) {
        Match match(raw_match, *this->tree);
        return match.capture_with_index(index);
    } else {
        return std::nullopt;
    }
}

std::vector<Match> QueryCursor::matches() {
    std::vector<Match> matches;

    while (std::optional<Match> match = this->next_match()) {
        matches.push_back(*match);
    }

    return matches;
}

} // namespace ts
