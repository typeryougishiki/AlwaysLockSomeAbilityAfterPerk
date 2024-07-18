#include "BGSEntryPoint.h"
#include "utils/Config.h"
namespace hook::BGSEntryPonint::HandleEntryPoint {
	void InnnerLogicFuncCallAfterDealVaArgs::thunk(RE::BGSEntryPoint::ENTRY_POINT a_entryPoint, RE::Actor* a_perkOwner, int64_t* a_va_list) {
		if (a_perkOwner != nullptr && a_perkOwner->IsPlayerRef() && Config::GetSingleton()->entry_point_need_perk_datas.count(a_entryPoint)) [[unlikely]] {
			logger::debug("EntryPoint {:x} handle on actor {:x}", static_cast<uint32_t>(a_entryPoint), a_perkOwner->formID);
			const auto& need_perk_data = Config::GetSingleton()->entry_point_need_perk_datas[a_entryPoint];
			bool suc = false;
			{
				RaiiGuard guard{ 
					[&a_perkOwner]() {a_perkOwner->perkArrayLock.lock_read(); },
					[&a_perkOwner]() {a_perkOwner->perkArrayLock.unlock_read(); } 
				};
				if(Config::debug_logging){
					for (const auto* ptr = a_perkOwner->perks->perkRanks->begin(); ptr != a_perkOwner->perks->perkRanks->end() && !suc; ptr++) {
						logger::debug("perk {} rank {}", ptr->perk->GetFormEditorID(),need_perk_data.rank);
					}
				}
				for (const auto* ptr = a_perkOwner->perks->perkRanks->begin(); ptr != a_perkOwner->perks->perkRanks->end() && !suc; ptr++) {
					if (need_perk_data.rank < ptr->currentRank) continue;
					if (ptr->perk->GetFormEditorID() == nullptr || ptr->perk->GetFormEditorIDLength() != need_perk_data.editor_id.size()) continue;
					if (need_perk_data.editor_id != ptr->perk->GetFormEditorID()) continue;
					suc = true;
				}
			}
			logger::debug("here  {}", suc);
			if (!suc) { return; }
		}
		func(a_entryPoint, a_perkOwner, a_va_list);
	}
}
