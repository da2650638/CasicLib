#include "TestMath.h"
#include "TestUtil.h"
#include "TestTrivallyDestructible.h"
#include "TestPOD.h"

#include "TMPLab/OptionalLab.h"



int main() 
{
	std::cout << std::boolalpha;

	TMPLab::_Optional_destruct_base<int> b1(TMPLab::in_place, 111);

	struct NonTrivialDestruct {
		~NonTrivialDestruct() {
			std::cout << "NonTrivialDestruct: ��Ȼ��ʲô�����ɣ���������������\n";
		}
	};
	TMPLab::_Optional_destruct_base< NonTrivialDestruct> b2(TMPLab::in_place);

	struct NoThrowCons {
		NoThrowCons(int i, float f) noexcept
		{
			std::cout << "������ʲô�쳣�����׳�\n";
		}
	};
	TMPLab::_Optional_destruct_base<NoThrowCons> b3(TMPLab::in_place, 1, 1.0f);
	std::cout << std::is_nothrow_constructible_v<NoThrowCons, int, float> << std::endl;

	// 1.ȷ��ƽ�ƺ���ת�Ա任��Ӱ��
	auto matTranslate = Casic::Math::Translate(1.0f, 1.0f, 0.0f);
	std::cout << "matTranslate: " << matTranslate;
	
	auto matRotation = Casic::Math::Rotate(45.0f, { 0.0f, 0.0f, 1.0f });
	std::cout << "matRotation: " << matRotation;

	auto matScale = Casic::Math::Scale({ 2.0f, 2.0f, 1.0f });
	std::cout << "matScale: " << matScale;

	auto transform = matTranslate * matRotation;
	std::cout << "����ת��ƽ��: " << transform;

	transform = matRotation * matTranslate;
	std::cout << "��ƽ������ת��" << transform;

	transform = matScale * matRotation;
	std::cout << "����ת�����ţ�" << transform;

	transform = matRotation * matScale;
	std::cout << "����������ת��" << transform;

	transform = matTranslate * matRotation * matScale;
	std::cout << "��������ת��ƽ�ƣ�" << transform;

	transform = matRotation * matScale * matTranslate;
	std::cout << "��ƽ����������ת��" << transform;

	return 0;
}