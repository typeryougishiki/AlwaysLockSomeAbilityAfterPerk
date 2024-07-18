// SFSE message listener, use this to do stuff at specific moments during runtime
#include"utils/Config.h"
#include "hook/BGSEntryPoint.h"
// Message Listener
void SfseMsgListener(SFSE::MessagingInterface::Message* message) noexcept {
    NoExceptField::Field([&message]() ->void {
        switch (message->type) {
        case SFSE::MessagingInterface::kPostLoad: {
        }break;
        case SFSE::MessagingInterface::kPostPostLoad: {
        }break;
        case SFSE::MessagingInterface::kPostDataLoad: {
        }break;
        case SFSE::MessagingInterface::kPostPostDataLoad: {
        }break;
        default: {
        }break;
        }
    });
}

// Main SFSE plugin entry point, initialize everything here
SFSEPluginLoad(const SFSE::LoadInterface* sfse){
    SFSE::Init(sfse);
    return NoExceptField::FieldWithReturn<bool>([]() ->auto {

        logger::info("{} {} is loading...", Plugin::Name, Plugin::Version.string());

        if (const auto messaging{ SFSE::GetMessagingInterface() }; !messaging->RegisterListener(SfseMsgListener))
            return false;
        logger::info("{} has finished loading.", Plugin::Name);
        hook::BGSEntryPonint::HandleEntryPoint::InnnerLogicFuncCallAfterDealVaArgs::Install();
        return true;

        }, false,"Init failed."
    );

}