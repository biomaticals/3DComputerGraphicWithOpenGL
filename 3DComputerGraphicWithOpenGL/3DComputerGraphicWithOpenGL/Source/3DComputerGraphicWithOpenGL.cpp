// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.
#include <stdio.h>
#include "iostream"
#include <GLFW/glfw3.h>

// Static Linked Library
#include "OutsideStaticMath.h"
#include "InsideStaticMath.h"

// Dynamic Linked Library
#include "InsideDynamicMath.h"
#include "OutsideDynamicMath.h"
 
void render(GLFWwindow* window);
 
int main()
{
    // glfw �ʱ�ȭ
    glfwInit();
 
    // window ����� (width, height, title, monitor, share)
    GLFWwindow* window = glfwCreateWindow(640, 480, "Inyong", 0, 0);
    
    // context�� �׸��� ���� ������ ��� ����
    // window�� �ΰ��̸� context�� �ΰ��ϼ��� ����
    // �׷��� � context�� �׸��� ������� ��
    glfwMakeContextCurrent(window);
 
    // ����ڰ� window â�� ���� ������
    while (!glfwWindowShouldClose(window)) {
        // window �׷��ֱ�
        render(window);
 
        // ���콺 �����̴� ��. �̷��͵� ���ͼ� �ʿ��� window���� �����ֱ�
        glfwPollEvents();
    }
 
    // window�� ������ ��� ������
    glfwDestroyWindow(window);
    glfwTerminate();
}
 
void render(GLFWwindow* window) { }