#ifndef INC_Common_MessageHandler_h
#define INC_Common_MessageHandler_h

// Internal Includes
#include <tvr/Common/RawMessageType.h>
#include <tvr/Common/RawSenderType.h>
#include <tvr/Util/SharedPtr.h>

// Library/third-party includes
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>

// Standard includes
#include <vector>

namespace tvr {
namespace common {
    class MessageHandlerBase : boost::noncopyable {
      public:
        virtual ~MessageHandlerBase();

      protected:
        MessageHandlerBase() {}
    };

    /// @brief A class template for the common message traits where the
    /// registrar is passed by pointer, has registerHandler and
    /// unregisterHandler methods, and doesn't take a RawSenderType because it's
    /// implied.
    template <typename Handler, typename Registrar>
    class ImpliedSenderMessageHandleTraits {
      public:
        typedef Handler handler_type;
        class registration_type {
          public:
            registration_type(Registrar *reg) : m_reg(reg) {}

            void registerHandler(handler_type handler, void *userdata,
                                 RawSenderType const &,
                                 RawMessageType const &msgType) {
                m_reg->registerHandler(handler, userdata, msgType);
            }
            void unregisterHandler(handler_type handler, void *userdata,
                                   RawSenderType const &,
                                   RawMessageType const &msgType) {
                m_reg->unregisterHandler(handler, userdata, msgType);
            }

          private:
            Registrar *m_reg;
        };
    };
    /// @brief RAII class template managing a message handler callback.
    ///
    /// @tparam MessageTraits Policy class, providing a `handler_type` typedef
    /// (function pointer type of this hander) and a `registration_type` type
    /// (holder class, passed in and stored by value on registration. Must
    /// contain `registerHandler` and `unregisterHandler` methods taking the
    /// arguments (HandlerType, void*, RawSenderType, RawMessageType) )
    template <typename MessageTraits>
    class MessageHandler : public MessageHandlerBase {
      public:
        typedef typename MessageTraits::handler_type handler_type;
        typedef typename MessageTraits::registration_type registration_type;

        /// @brief Constructor taking your handler's basic info, and optionally
        /// a sender, and optionally a message type
        MessageHandler(handler_type handler, void *userdata = nullptr,
                       RawSenderType sender = RawSenderType(),
                       RawMessageType msgType = RawMessageType())
            : m_handler(handler), m_data(userdata), m_sender(sender),
              m_msgType(msgType) {}

        /// @brief Constructor taking your handler's basic info and a message
        /// type
        ///
        /// Provided as an overload to take care of the case when only a message
        /// type is passed.
        MessageHandler(handler_type handler, void *userdata,
                       RawMessageType msgType)
            : m_handler(handler), m_data(userdata), m_msgType(msgType) {}

        /// @brief Method if you want to manually unregister your handler.
        ///
        /// Automatically done when object is destroyed. No effect if called
        /// before registerHandler()
        void unregisterHandler() {
            if (m_reg.is_initialized()) {
                m_reg->unregisterHandler(m_handler, m_data, m_sender,
                                         m_msgType);
                m_reg.reset();
            }
        }

        /// @brief Register handler on the given registration policy value.
        void registerHandler(registration_type reg) {
            unregisterHandler();
            m_reg = reg;
            m_reg->registerHandler(m_handler, m_data, m_sender, m_msgType);
        }

        /// @brief destructor: automatically unregisters handler.
        ~MessageHandler() { unregisterHandler(); }

      private:
        handler_type m_handler;
        void *m_data;
        RawSenderType m_sender;
        RawMessageType m_msgType;
        boost::optional<registration_type> m_reg;
    };

    template <typename MessageTraits>
    using MessageHandlerPtr = shared_ptr<MessageHandler<MessageTraits> >;

    template <typename MessageTraits>
    using MessageHandlerList = std::vector<MessageHandlerPtr<MessageTraits> >;

    typedef std::vector<shared_ptr<MessageHandlerBase> >
        GenericMessageHandlerList;
} // namespace common
} // namespace tvr
#endif // INCLUDED_MessageHandler_h_GUID_A7A258A7_A369_46BA_C44F_6FFE56DB464A
