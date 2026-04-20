#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

#include "httplib.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;


void firstExercise(){
    httplib::Client cli("http://jsonplaceholder.typicode.com");

    httplib::Result users = cli.Get("http://jsonplaceholder.typicode.com/users");

    if(users && users->status == 200){
        std::cout << "CONNECTION SUCCESSFUL" << std::endl;
        json json_user = json::parse(users->body);

        std::vector<std::pair<std::string,std::string>> namesAndEmailsBiz;

        for(const auto& user : json_user){
            if(user["email"].dump().find(".biz") != std::string::npos){
                namesAndEmailsBiz.push_back(std::make_pair(user["name"].dump(), user["email"].dump()));
            }
        }

        std::cout << "number of emails ending in .biz: " << namesAndEmailsBiz.size() << std::endl;
        for(int i = 0; i < namesAndEmailsBiz.size(); i++){
            std::cout << "Name: " << namesAndEmailsBiz[i].first << ", Email: " << namesAndEmailsBiz[i].second << std::endl;

        }
        
        
    }
}

void secondExercise(){
    httplib::Client cli("http://jsonplaceholder.typicode.com");
    httplib::Result todos = cli.Get("http://jsonplaceholder.typicode.com/todos");

    std::vector<std::string> incompleteTodoTitles;
    std::vector<std::string> completedTodoTitles;

    if(todos && todos->status == 200){
        std::cout << "CONNECTION SUCCESSFUL" << std::endl;

        json json_todos = json::parse(todos->body);

        for(const json& todo : json_todos){
            if(todo["completed"] == false && todo["userId"] == 1) incompleteTodoTitles.push_back(todo["title"].dump());
            else if(todo["completed"] == true && todo["userId"] == 1) completedTodoTitles.push_back(todo["title"].dump());
        }

        std::cout << "Number of incomplete todos for user 1: " << incompleteTodoTitles.size() << std::endl;
        for(const std::string title : incompleteTodoTitles) std::cout << "Title: " << title << std::endl;

        float ratio = (float)completedTodoTitles.size() / (float)incompleteTodoTitles.size();

        std::cout << "Ration between completed and incomplete todos for user 1: ";
        std::cout <<std::setprecision(2) << ratio << std::endl;


    } else {
        std::cout << "CONNECTION FAILED" << std::endl;
    }
    
    
}
void thirdExercise(){
    httplib::Client cli("http://jsonplaceholder.typicode.com");
    httplib::Result posts = cli.Get("http://jsonplaceholder.typicode.com/posts/1");

    if(posts && posts->status == 200){
        json json_post = json::parse(posts->body);

        json_post["title"] = "getting better at api's";
        json_post["timestamp"] = "April 20, 2026";

        posts = cli.Post("http://jsonplaceholder.typicode.com/posts", json_post.dump(), "application/json");

        if(posts && posts->status == 201){
            std::cout << "POST SUCCESSFUL" << std::endl;
            std::cout << "Response body: " << posts->body << std::endl;
        } else {
            std::cout << "POST FAILED" << std::endl;

        }
    }
}

int main() {
    
    return 0;
}
