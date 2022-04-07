#include "renderd7.hpp"

class Game : public RenderD7::Scene
{
    public:
    void Draw(void) const override;
    void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
    Game();
    ~Game();
    private:
    RenderD7::Sheet stuffs;
    RenderD7::Sprite bgn;
    RenderD7::Sprite bgd;
    RenderD7::Sprite ground[2];
    
};