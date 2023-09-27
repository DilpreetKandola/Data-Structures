
#include <iostream>
using namespace std;

class Permission {
  public:
    string role;
    string name;
    bool active;

    Permission() {}
    Permission(string role, string name, bool active) {
      this->role = role;
      this->name = name;
      this->active = active;
    }
};

class User {
  public:
    int id;
    string name;
    vector<string> roles;

    User() {}
    User(int id, string name, vector<string> roles) {
      this->id = id;
      this->name = name;
      this->roles = roles;
    }
};

//see graphic in instructions for visual explanation of the permission and user data structures
class Authorization {
  public:
    vector<User *> users;
    vector<Permission *> permissions;

    Authorization() {}
    Authorization(vector<Permission *> permissions, vector<User *> users) {
      this->permissions = permissions;
      this->users = users;
    }
    //  @rtype: vector of strings
    //  @returns: a vector of all the active permission names that the user with the corresponding user_id has
    //  @note: The order in which the permission names are returned is not important
    //  @example: listPermissions(1) ➡ ["View Orders", "Block User Account"] (purchased widgets not included since it 
    //  is not active)

vector<string> list_permissions(int user_id) {
    
    vector<string> userPermissions;
    
    for(User* user : users) {
        if(user->id == user_id){
            for(string role : user->roles){
                for(Permission* permission : permissions){
                    if(permission->role == role && permission->active){
                        userPermissions.push_back(permission->name);
                    }
                }
            }
        }
    }
    
    return userPermissions;
    
    
}

    //  @rtype: boolean value
    //  @returns: true or false based on if the user with the corresponding user_id has the role that corresponds with the specific permission_name and that particular permission is active
    //  @example: Example (Based on data from graphic)
    //  checkPermitted("scooters near me", 2) ➡ true
    //  checkPermitted("scooters near me", 1) ➡ false
bool check_permitted(string permission_name, int user_id){
    for(User* user : users){
        if(user->id == user_id){
            for(string role: user->roles){
                for(Permission* permission : permissions){
                    if(permission->role == role && permission->name == permission_name && permission->active){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}