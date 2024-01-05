//
// Created by Samuel on 02/01/2024.
//

#ifndef PAC_MAN_DIJKSTRAGRAPH_H
#define PAC_MAN_DIJKSTRAGRAPH_H
#include "DijkstraPoint.h"
#include "DijkstraTransition.h"

class Model::DijkstraGraph {
    std::vector<std::vector<std::shared_ptr<Model::Wall>>> world;
    std::shared_ptr<DijkstraPoint> beginPoint;
    std::shared_ptr<DijkstraPoint> endPoint;
    std::vector<std::shared_ptr<DijkstraPoint>> points;
    std::vector<std::vector<std::shared_ptr<DijkstraPoint>>> dijkstraMap;
public:
    DijkstraGraph(const std::vector<std::vector<std::shared_ptr<Model::Wall>>> &world,
                  const std::shared_ptr<DijkstraPoint> &beginPoint, const std::shared_ptr<DijkstraPoint> &endPoint);

    /*
     * Builds the DijkstraMap until it reaches it's target
     */
    void buildDijkstraMap();

    /*
     * Prints the dijkstraMap if you would want to
     */
    [[maybe_unused]] void printDijkstraMap();

    /*
     * Makes a vector of directions that need to be followed to reach the target
     */
    std::vector<direction> getDijkstraPath();

    [[nodiscard]] const std::shared_ptr<DijkstraPoint> &getBeginPoint() const;

    [[nodiscard]] const std::shared_ptr<DijkstraPoint> &getEndPoint() const;

    [[nodiscard]] const std::vector<std::vector<std::shared_ptr<Model::Wall>>> &getWorld() const;
};


#endif //PAC_MAN_DIJKSTRAGRAPH_H
