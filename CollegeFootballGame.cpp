#include <map>
#include <vector>
#include <string>
using namespace std;

class CollegeFootballGame;
class Player;
class TargetPractice;
class Ball;
class Target;
class PysicsEngine;
class StaticTarget;
class MovingTarget;
class ScoringZoneTarget;

class CollegeFootballGame{
    public:
        Player* players[100];
        TargetPractice* targetPractice[100];
        void startPractice(Player &p, TargetPractice &tp);
};

struct Vector2d {
    float x,y;
};

class Player{
    public:
        int pid;
        string name;
        Vector2d position;
        int exp;
        map<string,int> highScore; //highScore[challengeId] = value

        void kick(float kick,float angle);
        void updateExp(int points);
        int getHighScore(string challengeId); 
};

class TargetPractice{
    public:
        string challengeId[100];
        Ball* balls[100];
        Target* targets[100];
        PhysicsEngine physicsEngine;

        void runPractice(Player &p, string challengeId);
};

class Ball{
    public:
        Vector2d initialPosition;
        Vector2d currentPosition;
        int initialSpeed;
        int initialAngle;
};

class PhysicsEngine{
    public:
        Vector2d calculateTrajectory(Player &p, Ball &b);
};

class Target{
    public:
        Vector2d targetPosition;
        float radius;  

        virtual bool isHit(Ball &b) = 0;
};

class StaticTarget: public Target{};

class MovingTarget: public Target{
    public:
        Vector2d path[100];
        float speed;
};

class ScoringZoneTarget: public Target{
    public:
        map<int,int> zones; //zones[location] = points

        int calculateScore(Ball &b);
};