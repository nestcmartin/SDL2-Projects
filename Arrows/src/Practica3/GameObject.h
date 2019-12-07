#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void update() = 0;
	virtual void render() const = 0;
};

#endif // !__GAME_OBJECT_H__