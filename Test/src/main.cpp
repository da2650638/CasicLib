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
			std::cout << "NonTrivialDestruct: 虽然我什么都不干，但是你必须调用我\n";
		}
	};
	TMPLab::_Optional_destruct_base< NonTrivialDestruct> b2(TMPLab::in_place);

	struct NoThrowCons {
		NoThrowCons(int i, float f) noexcept
		{
			std::cout << "我现在什么异常都不抛出\n";
		}
	};
	TMPLab::_Optional_destruct_base<NoThrowCons> b3(TMPLab::in_place, 1, 1.0f);
	std::cout << std::is_nothrow_constructible_v<NoThrowCons, int, float> << std::endl;

	// 1.确认平移和旋转对变换的影响
	auto matTranslate = Casic::Math::Translate(1.0f, 1.0f, 0.0f);
	std::cout << "matTranslate: " << matTranslate;
	
	auto matRotation = Casic::Math::Rotate(45.0f, { 0.0f, 0.0f, 1.0f });
	std::cout << "matRotation: " << matRotation;

	auto matScale = Casic::Math::Scale({ 2.0f, 2.0f, 1.0f });
	std::cout << "matScale: " << matScale;

	auto transform = matTranslate * matRotation;
	std::cout << "先旋转再平移: " << transform;

	transform = matRotation * matTranslate;
	std::cout << "先平移再旋转：" << transform;

	transform = matScale * matRotation;
	std::cout << "先旋转再缩放：" << transform;

	transform = matRotation * matScale;
	std::cout << "先缩放再旋转：" << transform;

	transform = matTranslate * matRotation * matScale;
	std::cout << "先缩放旋转再平移：" << transform;

	transform = matRotation * matScale * matTranslate;
	std::cout << "先平移再缩放旋转：" << transform;

	return 0;
}