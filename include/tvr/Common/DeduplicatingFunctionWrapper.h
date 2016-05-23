#ifndef INC_Common_DeduplicatingFunctionWrapper_h
#define INC_Common_DeduplicatingFunctionWrapper_h

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <functional>
#include <type_traits>
#include <stdexcept>

namespace tvr {
namespace common {
    /// @brief A wrapper for a unary function that only calls its contained
    /// function when the input has changed.
    template <typename ArgumentType, typename StorageType = void>
    class DeduplicatingFunctionWrapper {
      public:
        /// @brief Argument type: always must be supplied via template parameter
        using argument_type = ArgumentType;

        /// @brief Storage type: if not supplied via template parameter,
        /// inferred by removing const& from the argument type.
        using storage_type = typename std::conditional<
            std::is_same<StorageType, void>::value,
            typename std::remove_const<
                typename std::remove_reference<ArgumentType>::type>::type,
            StorageType>::type;

        /// @brief Return type - presently fixed.
        typedef void return_type;

        /// @brief std::function type corresponding to what is being wrapped.
        typedef std::function<return_type(argument_type)> function_type;

        /// @brief Constructor from a function
        explicit DeduplicatingFunctionWrapper(function_type const &f)
            : m_func(f), m_beenCalled(false) {}

        /// @brief Default constructor - must have function set before calling.
        DeduplicatingFunctionWrapper() : m_beenCalled(false) {}

        /// @brief Set/replace the function.
        void setFunction(function_type const &f) { m_func = f; }

        /// @brief Function call operator: passes call along to contained
        /// function if and only if (argument != last argument) or (first time
        /// being called)
        ///
        /// Takes and throws away extra arguments so you don't have to wrap it
        /// in std::bind to get flexible calling ability.
        return_type operator()(argument_type arg, ...) {
            if (!m_func) {
                throw std::logic_error("Must set the function in "
                                       "DeduplicatingFunctionWrapper before "
                                       "calling it!");
            }
            if (!m_beenCalled) {
                // First call - always pass through.
                m_beenCalled = true;
                return m_do(arg);
            }
            if (arg != m_last) {
                // Not first call, but argument has changed
                return m_do(arg);
            }
            return m_defaultReturn();
        }

      private:
        /// @brief Helper to create the default return value, in possible
        /// anticipation of a non-void and policy-based default return value.
        static return_type m_defaultReturn() { return return_type(); }

        /// @brief Helper to actually update the last input and perform
        /// invocation
        return_type m_do(argument_type arg) {
            m_last = arg;
            return m_func(arg);
        }

        /// @brief wrapped function
        function_type m_func;

        /// @brief have we been called yet?
        bool m_beenCalled;

        /// @brief last argument - valid only if m_beenCalled
        storage_type m_last;
    };
}
}

#endif
