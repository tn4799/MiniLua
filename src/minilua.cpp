#include "MiniLua/MiniLua.hpp"
#include <ios>
#include <iostream>
#include <utility>
#include <variant>

namespace minilua {

// TODO should be in utility header
// template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// value types
//
// struct Nil
constexpr auto operator==(Nil, Nil) noexcept -> bool { return true; }
constexpr auto operator!=(Nil, Nil) noexcept -> bool { return false; }
auto operator<<(std::ostream& o, Nil) -> std::ostream& { return o << "nil"; }

// struct Bool
constexpr Bool::Bool(bool value) : value(value) {}

constexpr auto operator==(Bool a, Bool b) noexcept -> bool { return a.value == b.value; }
constexpr auto operator!=(Bool a, Bool b) noexcept -> bool { return !(a == b); }
auto operator<<(std::ostream& o, Bool self) -> std::ostream& {
    return o << std::boolalpha << self.value << std::noboolalpha;
}

// struct Number
// constexpr Number::Number(int value) : value(value) {}
constexpr Number::Number(double value) : value(value) {}

constexpr auto operator==(Number a, Number b) noexcept -> bool { return a.value == b.value; }
constexpr auto operator!=(Number a, Number b) noexcept -> bool { return !(a == b); }
constexpr auto operator<(Number a, Number b) noexcept -> bool { return a.value < b.value; }
constexpr auto operator>(Number a, Number b) noexcept -> bool { return a.value > b.value; }
constexpr auto operator<=(Number a, Number b) noexcept -> bool { return a.value <= b.value; }
constexpr auto operator>=(Number a, Number b) noexcept -> bool { return a.value >= b.value; }
auto operator<<(std::ostream& o, Number self) -> std::ostream& { return o << self.value; }

// struct String
String::String(std::string value) : value(value) {}

auto operator==(const String& a, const String& b) noexcept -> bool { return a.value == b.value; }
auto operator!=(const String& a, const String& b) noexcept -> bool { return !(a == b); }
auto operator<<(std::ostream& o, const String& self) -> std::ostream& {
    return o << "\"" << self.value << "\"";
}

// struct Table
struct Table::Impl {
    std::unordered_map<Value, Value> value;
};
Table::Table() = default;
Table::Table(std::unordered_map<Value, Value> value)
    : impl(make_owning<Impl>(Impl{.value = std::move(value)})) {}
Table::Table(std::initializer_list<std::pair<const Value, Value>> values) {
    for (const auto& [key, value] : values) {
        this->impl->value.insert_or_assign(key, value);
        std::cout << "\t" << key << " = " << value << "\n";
    }
    std::cout << "new Table: " << *this << "\n";
}

Table::Table(const Table& other) : impl(other.impl) {}
Table::Table(Table&& other) noexcept : impl(other.impl) {}
Table::~Table() noexcept = default;
auto Table::operator=(const Table& other) -> Table& {
    impl = other.impl;
    return *this;
}
auto Table::operator=(Table&& other) -> Table& {
    swap(*this, other);
    return *this;
}
void swap(Table& self, Table& other) { std::swap(self.impl, other.impl); }

auto operator==(const Table& a, const Table& b) noexcept -> bool {
    return a.impl->value == b.impl->value;
}
auto operator!=(const Table& a, const Table& b) noexcept -> bool { return !(a == b); }
auto operator<<(std::ostream& o, const Table& self) -> std::ostream& {
    o << "{";

    for (const auto& [key, value] : self.impl->value) {
        o << "[" << key << "] = " << value << ", ";
    }

    return o << "}";
}

// struct NativeFunction
auto operator<<(std::ostream& o, const NativeFunction&) -> std::ostream& {
    return o << "<NativeFunction>";
}

// class Value
struct Value::Impl {
    Type val;
};

Value::Value() = default;
Value::Value(Value::Type val) : impl(make_owning<Impl>(Impl{.val = std::move(val)})) {
    std::cout << "Value(std::variant)\n";
}
Value::Value(Nil val) : impl(make_owning<Impl>(Impl{.val = val})) { std::cout << "Value(Nil)\n"; }
Value::Value(Bool val) : impl(make_owning<Impl>(Impl{.val = val})) {
    std::cout << "Value(Bool: " << val << ")\n";
}
Value::Value(bool val) : Value(Bool(val)) { std::cout << "Value(bool)\n"; }
Value::Value(Number val) : impl(make_owning<Impl>(Impl{.val = val})) {
    std::cout << "Value(Number: " << val << ")\n";
}
Value::Value(int val) : Value(Number(val)) { std::cout << "Value(int)\n"; }
Value::Value(double val) : Value(Number(val)) { std::cout << "Value(double)\n"; }
Value::Value(String val) : impl(make_owning<Impl>(Impl{.val = val})) {
    std::cout << "Value(String)\n";
}
Value::Value(std::string val) : Value(String(std::move(val))) {
    std::cout << "Value(std::string)\n";
}
Value::Value(const char* val) : Value(String(val)) { std::cout << "Value(const char*)\n"; }
Value::Value(Table val) : impl(make_owning<Impl>(Impl{.val = val})) {
    std::cout << "Value(Table)\n";
}
Value::Value(NativeFunction val) : impl(make_owning<Impl>(Impl{.val = val})) {
    std::cout << "Value(NativeFunction)\n";
}

Value::Value(const Value& other) = default;
Value::Value(Value&& other) noexcept = default;
Value::~Value() = default;
auto Value::operator=(const Value& other) -> Value& = default;
auto Value::operator=(Value&& other) -> Value& = default;
void swap(Value& self, Value& other) { std::swap(self.impl, other.impl); }

auto Value::get() -> Value::Type& { return impl->val; }
auto Value::get() const -> const Value::Type& { return impl->val; }

auto operator==(const Value& a, const Value& b) noexcept -> bool { return a.get() == b.get(); }
auto operator!=(const Value& a, const Value& b) noexcept -> bool { return !(a == b); }
auto operator<<(std::ostream& o, const Value& self) -> std::ostream& {
    std::visit([&](const auto& value) { o << value; }, self.get());

    return o;
}

struct CallContext::Impl {
    Range location;
    Environment& env;
    Vallist args;
};
CallContext::CallContext(Environment& env) : impl(make_owning<Impl>(Impl{.env = env})) {}
CallContext::CallContext(const CallContext& other) = default;
CallContext::CallContext(CallContext&& other) noexcept = default;
CallContext::~CallContext() = default;

auto CallContext::call_location() const -> Range { return impl->location; }
auto CallContext::environment() const -> Environment& { return impl->env; }
auto CallContext::get(std::string name) const -> Value& { return impl->env.get(name); }
auto CallContext::arguments() const -> const Vallist& { return impl->args; }

void Environment::add_default_stdlib() {}
void Environment::add(std::string name, Value value) { global.insert_or_assign(name, value); }

void Environment::add_all(std::unordered_map<std::string, Value> values) {
    global.insert(values.begin(), values.end());
}
void Environment::add_all(std::initializer_list<std::pair<const std::string, Value>> values) {
    global.insert(values.begin(), values.end());
}

auto Environment::get(const std::string& name) -> Value& { return this->global.at(name); }

auto operator==(const Environment& a, const Environment& b) noexcept -> bool {
    return a.global == b.global;
}
auto operator!=(const Environment& a, const Environment& b) noexcept -> bool { return !(a == b); }
auto operator<<(std::ostream& o, const Environment& self) -> std::ostream& {
    o << "Environment {";

    for (const auto& [key, value] : self.global) {
        o << "[\"" << key << "\"] = " << value << ", ";
    }

    return o << "}";
}

class Parser {
    std::string source;

public:
    Parser(std::string source) : source(std::move(source)) {}
};

class Tree {};

struct Interpreter::Impl {
    Parser parser;
    Tree tree;
    Environment env;

    Impl(Parser parser, Environment env) : parser(parser), env(std::move(env)) {}

    void parse(std::string source) {
        // TODO
        std::cout << "parse\n";
    }

    void apply_source_changes(std::vector<SourceChange> changes) {
        // TODO
        std::cout << "apply_source_changes\n";
    }

    auto run() -> EvalResult {
        std::cout << "run\n";
        // TODO
        return EvalResult();
    }
};

Interpreter::Interpreter() : Interpreter("") {}
Interpreter::Interpreter(std::string initial_source_code)
    : impl(std::make_unique<Interpreter::Impl>(
          Parser(std::move(initial_source_code)), Environment())) {
    // TODO initialize parser with source code
}
Interpreter::~Interpreter() = default;

auto Interpreter::environment() -> Environment& { return impl->env; }
void Interpreter::parse(std::string source_code) { impl->parse(std::move(source_code)); }
void Interpreter::apply_source_changes(std::vector<SourceChange> changes) {
    impl->apply_source_changes(std::move(changes));
}
auto Interpreter::run() -> EvalResult { return impl->run(); }

CallResult::CallResult() { std::cout << "CallResult\n"; }
CallResult::CallResult(Vallist) { std::cout << "CallResult(Vallist)\n"; }
CallResult::CallResult(std::vector<Value> values) : CallResult(Vallist(values)) {}
CallResult::CallResult(std::initializer_list<Value> values) : CallResult(Vallist(values)) {}
CallResult::CallResult(SourceChange) { std::cout << "CallResult(SourceChange)\n"; }
CallResult::CallResult(Vallist, SourceChange) {
    std::cout << "CallResult(Vallist, SourceChange)\n";
}

// class Vallist
struct Vallist::Impl {
    std::vector<Value> values;
};
Vallist::Vallist() { std::cout << "Vallist()\n"; }
Vallist::Vallist(std::vector<Value>) { std::cout << "Vallist(vector)\n"; }
Vallist::Vallist(std::initializer_list<Value>) { std::cout << "Vallist(<init-list>)\n"; }

Vallist::Vallist(const Vallist&) = default;
Vallist::Vallist(Vallist&&) noexcept = default;
Vallist::~Vallist() = default;

auto Vallist::size() const -> size_t { return impl->values.size(); }
auto Vallist::get(size_t index) const -> const Value& { return impl->values.at(index); }
auto Vallist::begin() const -> std::vector<Value>::const_iterator { return impl->values.cbegin(); }
auto Vallist::end() const -> std::vector<Value>::const_iterator { return impl->values.cend(); }

} // namespace minilua
