#ifndef __ABSTRACTENTITY_H__
#define __ABSTRACTENTITY_H__

#include <string>

using namespace std;
enum Type {Virus, Data, Serverport, Firewall};
class AbstractEntity {
    protected:
        int id;
        size_t x, y;
        char appearance;
        Type type;
        string owner;
    public:
     AbstractEntity(int id, size_t x, size_t y, char appearance, Type type, string owner): 
                    id{id}, x{x}, y{y}, appearance{appearance}, type{type}, owner{owner} {
          
     }

     virtual ~AbstractEntity() {}

     size_t getX() const {
          return x;
     }
     size_t getY() const {
          return y; 
     }

     char getAppearance() const {
          return appearance; 
     }
     int getID() {
          return id;
     }


     void setX(size_t newX) {
     this->x = newX;
     }


     void setY(size_t newY) {
          this->y = newY;
     }

     string getOwner() {
          return owner;
     }

     void setType(Type t) {
          this->type = t;
     }

     virtual Type getType() const = 0;

};

#endif