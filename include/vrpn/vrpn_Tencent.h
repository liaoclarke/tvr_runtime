#pragma once

#include "vrpn_HumanInterface.h"
#include "vrpn_Analog.h"
#include "vrpn_Poser.h"
#include "vrpn_Tracker.h"
#include "vrpn_Button.h"
#include "vrpn_Configure.h"

#if defined(VRPN_USE_HID)

class vrpn_Tencent : public vrpn_Analog, protected vrpn_HidInterface {
    public:
        virtual ~vrpn_Tencent();
        virtual void mainloop();

    protected:
        vrpn_Tencent(vrpn_uint16 product_id, vrpn_uint8 num_channels, const char *name, vrpn_Connection *c= NULL, double keepAliveSeconds = 9.0);
        vrpn_HidAcceptor *m_filter;
        virtual bool parse_message(std::size_t bytes, vrpn_uint8 *buffer);
        void parse_message_type_1(std::size_t bytes, vrpn_uint8 *buffer);
        void on_data_received(std::size_t bytes, vrpn_uint8 *buffer);
        struct timeval d_timestamp;
        double d_keepAliveSeconds;
        struct timeval d_lastKeepAlive;
        virtual void writeKeepAlive(vrpn_uint16 interval = 10000, vrpn_uint16 commandId = 0) = 0;
};

class vrpn_Tencent_DK0 : public vrpn_Tencent {
    public:
        vrpn_Tencent_DK0(const char *name, vrpn_Connection *c = NULL, double keepAliveSeconds = 9.0);
        void VRPN_CALLBACK register_poser_handler(void* userdata, vrpn_POSERHANDLER handler);
        void VRPN_CALLBACK register_pos_handler(void* userdata, vrpn_TRACKERCHANGEHANDLER handler);
        void VRPN_CALLBACK register_vel_handler(void* userdata, vrpn_TRACKERVELCHANGEHANDLER handler);
        void VRPN_CALLBACK register_acc_handler(void* userdata, vrpn_TRACKERACCCHANGEHANDLER handler);
        void VRPN_CALLBACK register_button_handler(void* userdata, vrpn_BUTTONCHANGEHANDLER handler);

    protected:
        virtual void writeKeepAlive(vrpn_uint16 interval = 10000, vrpn_uint16 commandId = 0);
};
#endif
