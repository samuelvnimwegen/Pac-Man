//
// Created by Samuel on 16/11/2023.
//

#include "Score.h"
#include "cmath"
#include "fstream"
#include "algorithm"

Model::Score::Score(const std::weak_ptr<Model::World> &world) : world(world) {
    score = 0;
    lastCollected = 0;
    levelStartTime = 0;
    benchMarkTime = 0;
    scoreBoardFileName = "ScoreBoard.txt";
    this->loadScoreBoard();
}

double Model::Score::getAmplifyingFactor(){
    auto stopwatch = Model::Stopwatch::instance();
    // Als dit de eerste collectable is die in dit level collected wordt, geeft deze score * 1
    if (this->getLastCollected() == 0){
        this->setLastCollected(stopwatch->getTotalSeconds());
        return 1;
    }
    // Als het meer als een halve seconde geleden was voor de vorige fruit, wordt er per seconde dat het langer duurt
    // dan deze halve seconde 20% van de factor afgetrokken met als minimum 0.10 of 10% van de maximaal behaalbare score.
    else{
        double secondsSinceLastCollectable = stopwatch->getTotalSeconds() - this->getLastCollected();
        this->setLastCollected(stopwatch->getTotalSeconds());
        double factor = 1;
        if (secondsSinceLastCollectable > 0.5){
            factor -= secondsSinceLastCollectable / 5;
        }
        if (factor > 0.1){
            return factor;
        }
        else{
            return 0.1;
        }
    }

}

int Model::Score::getScore() const {
    return score;
}

const std::string &Model::Score::getScoreBoardFileName() const {
    return scoreBoardFileName;
}

double Model::Score::getLastCollected() const {
    return lastCollected;
}

double Model::Score::getLevelStartTime() const {
    return levelStartTime;
}

const std::weak_ptr<Model::World> &Model::Score::getWorld() const {
    return world;
}

void Model::Score::setLastCollected(double collected) {
    Score::lastCollected = collected;
}

void Model::Score::setLevelStartTime(double startTime) {
    Score::levelStartTime = startTime;
}

void Model::Score::setScore(int i) {
    Score::score = i;
}

double Model::Score::getBenchMarkTime() const {
    return benchMarkTime;
}

void Model::Score::setBenchMarkTime(double d) {
    Score::benchMarkTime = d;
}

void Model::Score::loadScoreBoard() {
    scoreBoard.clear(); // Oude opgeslagen scoreboard clearen
    std::ifstream file(this->getScoreBoardFileName().c_str());

    // ScoreBoard-file moet bestaan om ze in te kunnen laden:
    if (file.is_open()){
        std::string line;
        while (std::getline(file, line)){
            this->scoreBoard.push_back(stoi(line));
        }
        file.close();
    }

}

void Model::Score::storeScoreBoard() {
    // Huidige score toevoegen en daarna sorteren in dalende orde
    this->scoreBoard.push_back(this->getScore());
    std::sort(this->scoreBoard.begin(), this->scoreBoard.end(), std::greater());

    // Top 5 scores in file opslaan:
    try{
        std::ofstream outputFile(this->getScoreBoardFileName().c_str());
        if (outputFile.is_open()){
            for (int i = 0; (i < 5 and i < this->getScoreBoard().size()); ++i){
                outputFile << this->getScoreBoard().at(i) << std::endl;
            }
            outputFile.close();
        }else{
            throw std::runtime_error("ScoreBoard outfile couldn't be made");
        }
    }
    catch (std::runtime_error& e){
        std::cout << "An error occurred: " << e.what() << std::endl;
    }
}

const std::vector<int> &Model::Score::getScoreBoard() const {
    return scoreBoard;
}

void Model::Score::ghostConsumed() {
    this->setScore(this->getScore() + 100);
}


