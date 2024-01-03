    //
    // Created by Samuel on 16/11/2023.
    //
    #ifndef PAC_MAN_WALL_H
    #define PAC_MAN_WALL_H
    #include "EntityModel.h"
    #include "Observer.h"

    class Model::Wall: public Model::EntityModel{
    public:
        Wall(int row, int col);

        void update(const double &seconds) override;
    };


    #endif //PAC_MAN_WALL_H
