#pragma once
#include "SimpleIni.h"
#include "EntryPointTable.h"
class Config : public Singleton<Config>{
public:
    struct EntryPointNeedPerkData { std::string editor_id; uint8_t rank; };
    std::unordered_map<RE::BGSEntryPoint::ENTRY_POINT, EntryPointNeedPerkData> entry_point_need_perk_datas;
    inline static void LoadSettings() noexcept
    {
        logger::info("Loading settings");

        CSimpleIniA ini;

        ini.SetUnicode();
        if ((ini.LoadFile(Plugin::ConfigPath.data()) <=> 0) < 0) {
            logger::error("ERROR: Failed to load ini");
            return;
        }

        debug_logging = ini.GetBoolValue("Log", "Debug");

        if (debug_logging) {
            spdlog::set_level(spdlog::level::level_enum::debug);
            logger::debug("Debug logging enabled");
        }

        // Load settings (see simpleini readme: https://github.com/brofield/simpleini)
        for (auto& d : ENTRY_POINT_TABLE) {
            auto raw_editor_id_rank = ini.GetValue("EntryPoint", d.name.data());
            if (raw_editor_id_rank != nullptr) {
                std::string_view editor_id_rank{ raw_editor_id_rank };
                auto split_index = editor_id_rank.find(',');
                if (split_index == -1) {
                    GetSingleton()->entry_point_need_perk_datas.emplace(d.entry_point, EntryPointNeedPerkData{std::string(editor_id_rank), 1});
                }
                else {
                    auto editor_id = editor_id_rank.substr(0, split_index);
                    auto rank_str = editor_id_rank.substr(split_index + 1, editor_id_rank.size() - (split_index + 1));
                    uint8_t rank = 0;
                    auto statu = std::from_chars(rank_str.data(), rank_str.data() + rank_str.size(), rank);
                    if (statu.ec == std::errc::invalid_argument ||  statu.ptr != rank_str.data() + rank_str.size()) {
                        logger::error("Unable get perk rank in '{}':Could not convert.",editor_id_rank);
                        logger::error("Use 0 as '{}' rank", editor_id);
                        rank = 0;
                    }
                    GetSingleton()->entry_point_need_perk_datas.emplace(d.entry_point, EntryPointNeedPerkData{ std::string(editor_id), rank });
                }
            }
        }
        logger::info("Loaded settings");
    };

    inline static bool debug_logging{};
};