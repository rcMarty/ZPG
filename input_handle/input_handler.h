//
// Created by rc_marty on 11.10.23.
//
#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "stdio.h"
#include <memory>
#include <vector>
#include <functional>


namespace input {

    struct Mouse_btn_event_data {
        int button;
        int action;
        int mode;
        double x;
        double y;
    };
    struct Key_event_data {
        int key;
        int scancode;
        int action;
        int mods;
    };
    struct Cursor_event_data {
        double x;
        double y;
    };


    class Input_handler {
    private:
        std::vector<std::function<void(Mouse_btn_event_data)>> mouse_btn_callbacks;
        std::vector<std::function<void(Key_event_data)>> key_callbacks;
        std::vector<std::function<void(Cursor_event_data)>> cursor_callbacks;


    public:

        bool pressed_keys[1024];

        void notify(Mouse_btn_event_data data) {
            for (auto &callback: mouse_btn_callbacks) {
                callback(data);
            }
        };

        void notify(Key_event_data data) {
            //printf("[DEBUG] notifying %d callbacks\n", key_callbacks.size());
            for (auto &callback: key_callbacks) {
                callback(data);
            }
        };

        void notify(Cursor_event_data data) {
            //printf("[DEBUG] notifying %d callbacks\n", key_callbacks.size());
            for (auto &callback: cursor_callbacks) {
                callback(data);
            }
        };

        void subscribe(std::function<void(Mouse_btn_event_data)> callback) {
            mouse_btn_callbacks.push_back(callback);
        };

        void subscribe(std::function<void(Key_event_data)> callback) {
            key_callbacks.push_back(callback);
        };

        void subscribe(std::function<void(Cursor_event_data)> callback) {
            cursor_callbacks.push_back(callback);
        };

    };

    static void mouse_btn_callback(GLFWwindow *window, int button, int action, int mode) {
        auto aaa = static_cast<Input_handler *>( glfwGetWindowUserPointer(window));
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        aaa->notify(Mouse_btn_event_data{button, action, mode, x, y});
    }

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto aaa = static_cast<Input_handler *>( glfwGetWindowUserPointer(window));
        aaa->notify(Key_event_data{key, scancode, action, mods});
    }

    static void window_focus_callback(GLFWwindow *window, int focused) {
        printf("window_focus_callback \n");
    }

    static void window_iconify_callback(GLFWwindow *window, int iconified) {
        printf("window_iconify_callback \n");
    }

    static void window_size_callback(GLFWwindow *window, int width, int height) {
        printf("resize %d, %d \n", width, height);
        glViewport(0, 0, width, height);
    }

    static void cursor_callback(GLFWwindow *window, double x, double y) {
        //printf("cursor_callback %f, %f \n", x, y);
        auto aaa = static_cast<Input_handler *>( glfwGetWindowUserPointer(window));
        aaa->notify(Cursor_event_data{x, y});
    }


}