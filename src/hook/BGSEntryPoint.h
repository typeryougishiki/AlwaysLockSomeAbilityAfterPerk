namespace hook::BGSEntryPonint::HandleEntryPoint{
	constexpr auto FUNCTION_ID{ REL::ID(110912) };
	struct InnnerLogicFuncCallAfterDealVaArgs {
		//HandleEntryPoint函数（REL::ID(110912)）仅在处理变长参数后调用实际的逻辑处理函数
		//此处hook对实际的逻辑处理函数的调用
		inline constexpr static std::ptrdiff_t CALL_LOCATION{ 0x17 };//对该函数调用call指令相对于EquipObject函数起始点的偏移量
		static void thunk(RE::BGSEntryPoint::ENTRY_POINT a_entryPoint, RE::Actor* a_perkOwner,int64_t* va_list);
		inline static REL::Relocation<decltype(thunk)> func;
		inline static auto GetOrginialFunc() { return func; }
		inline static void Install() {
			REL::Relocation<std::uintptr_t> target{ FUNCTION_ID, CALL_LOCATION };
			stl::write_thunk_call<InnnerLogicFuncCallAfterDealVaArgs>(target.address());
			spdlog::info("'{}' HandleEntryPoint hook Install Sucess",Plugin::Name);
		}
	};
}