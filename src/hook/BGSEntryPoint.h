namespace hook::BGSEntryPonint::HandleEntryPoint{
	constexpr auto FUNCTION_ID{ REL::ID(110912) };
	struct InnnerLogicFuncCallAfterDealVaArgs {
		//HandleEntryPoint������REL::ID(110912)�����ڴ���䳤���������ʵ�ʵ��߼�������
		//�˴�hook��ʵ�ʵ��߼��������ĵ���
		inline constexpr static std::ptrdiff_t CALL_LOCATION{ 0x17 };//�Ըú�������callָ�������EquipObject������ʼ���ƫ����
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