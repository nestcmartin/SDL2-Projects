#ifndef __ECS__
#define __ECS__

#include <ctime>

namespace ECS
{
	// Identificadores un�vocos para los Componentes
	// Cuando se crea un componente debe registrarse
	// El �ltimo valor NO se debe modificar
	using CmpIdType = std::size_t;
	enum ComponentId : CmpIdType {
		Transform = 0,
		VelocityVectorViewer,
		FighterViewer,
		Health,
		FighterCtrl,
		Gun,
		FighterMotion,
		AsteroidsPool,
		AsteroidsMotion,
		AsteroidsViewer,
		BulletsPool,
		BulletsMotion,
		BulletsViewer,
		GameCtrl,
		ScoreManager,
		ScoreViewer,
		GameLogic,
		// YOU SHALL NOT PASS
		_LastCmptId_
	};

	// El valor del n�mero m�ximo de componentes depende 
	// del n�mero de componentes registrados
	constexpr std::size_t maxComponents = _LastCmptId_;

// Se devuelve un componente a partir del atributo entity_
#define GETCMP1_(type)       GETCMP3(entity_, ECS::type, type)
#define GETCMP2_(id, type)   GETCMP3(entity_, id, type)

// Se devuelve un componente a partir del par�metro e
#define GETCMP2(e, type)     GETCMP3(e, ECS::type, type)
#define GETCMP3(e, id, type) e->getComponent<type>(id)
}

#endif // !__ECS__