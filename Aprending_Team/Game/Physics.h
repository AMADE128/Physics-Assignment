#include "Source/Module.h"

class Physics : public Module
{
public:

	Physics();
    ~Physics();

	bool Start() override;

	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;

	bool CleanUp() override;


private:
};
