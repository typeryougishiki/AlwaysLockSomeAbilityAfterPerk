#pragma once
struct EntryPointData {
    RE::BGSEntryPoint::ENTRY_POINT entry_point;
    std::string_view name;
};
#define AddEntryPointData(point_name) EntryPointData{RE::BGSEntryPoint::ENTRY_POINT::##point_name,#point_name""sv}
static constexpr std::array<EntryPointData, 2> ENTRY_POINT_TABLE = {
    AddEntryPointData(kAllowJetpack),
    AddEntryPointData(kAllowPickpocket)
};