#ifndef MINILUA_INTERPRETER_H
#define MINILUA_INTERPRETER_H

#include <memory>
#include <string>
#include <vector>

#include "environment.hpp"
#include "source_change.hpp"
#include "values.hpp"

namespace minilua {

/**
 * Result of calling Interpreter::parse.
 *
 * Contains a list of errors and can be converted to a bool.
 * True means sucessful parse, false means there are errors.
 */
struct ParseResult {
    std::vector<std::string> errors; // NOLINT(misc-non-private-member-variables-in-classes)

    operator bool() const;
};

/**
 * Result of calling Interpreter::evaluate.
 *
 * Contains the return value of the lua code (if any)
 * and the produced source changes.
 */
struct EvalResult {
    Value value;
    std::optional<SourceChangeTree> source_change;
};

auto operator<<(std::ostream&, const EvalResult&) -> std::ostream&;

struct InterpreterConfig {
    bool trace_nodes;

    InterpreterConfig();
};

/**
 * An interpreter instance is used to parse and evaluate lua source code.
 *
 * You can create the interpreter with initial source code or empty source code
 * and then update the source code by calling 'parse' and run the current source
 * code by calling 'evaluate'.
 *
 * You can also apply a source change that was generated by the interpreter
 * while evaluating and get the updated source code.
 *
 * # Example
 *
 * ```
 * minilua::Interpreter interpreter{initial_source_code};
 * interpreter.parse(new_source_code);
 * auto res = interpreter.evaluate();
 * if (res.source_change) {
 *   interpreter.apply_source_change(res.source_change);
 * }
 * interpreter.evaluate();
 * ```
 */
class Interpreter {
    struct Impl;
    std::unique_ptr<Impl> impl;

    InterpreterConfig _config;

public:
    /**
     * Initializes the interpreter with empty source code
     */
    Interpreter();

    /**
     * Initializes the interpreter with the given source code
     *
     * Throws an exception if there was an error parsing the source code.
     */
    Interpreter(std::string initial_source_code);

    ~Interpreter();

    /**
     * Returns the current configuration.
     */
    auto config() -> InterpreterConfig&;
    [[nodiscard]] auto config() const -> const InterpreterConfig&;
    void set_config(InterpreterConfig);

    /**
     * Returns the environment for modification.
     *
     * NOTE: This will not directly be used by the interpreter so you can just
     * reuse an existing interpreter/environment without resetting it.
     */
    [[nodiscard]] auto environment() const -> Environment&;

    /**
     * Returns a view into the current source code.
     *
     * The returned value will become invalid if the source code is changed
     * (by calling parse or apply_source_changes).
     */
    [[nodiscard]] auto source_code() const -> std::string_view;

    /**
     * Parse fresh source code.
     *
     * Errors are returned in 'ParseResult'.
     */
    auto parse(std::string source_code) -> ParseResult;

    /**
     * Applies a list of single source changes.
     */
    void apply_source_changes(std::vector<SourceChange>);

    /**
     * Run the parsed program.
     *
     * Throws an exception when there is an error in the program.
     * E.g. when you try to add incompatible values in lua.
     *
     * Currently this throws 'std::runtime_error'.
     */
    auto evaluate() -> EvalResult;
};

}; // namespace minilua

#endif
