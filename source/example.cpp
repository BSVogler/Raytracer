#include "fensterchen.hpp"

int main(int argc, char* argv[])
{
  Window win{{800,800}};

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    auto t = win.getTime();
    glm::vec2 p1(0.5 + 0.5 * std::sin(t), 0.5 + 0.5 * std::cos(t));
    glm::vec2 p2(0.5 + 0.5 * std::sin(2.0*t), 0.5 + 0.5 * std::cos(2.0*t));
    glm::vec2 p3(0.5 + 0.5 * std::sin(t-10.f), 0.5 + 0.5 * std::cos(t-10.f));

    win.drawPoint(p1, Color(255, 0, 0));
    win.drawPoint(p2, Color(0, 255, 0));
    win.drawPoint(p3, Color(0, 0, 255));

    auto m = win.mousePosition();
    win.drawLine(glm::vec2(0.1f,0.1f), glm::vec2(0.8f,0.1f), Color(255,0,0));

    win.drawLine(glm::vec2(0.0f, m.y), glm::vec2(0.01f, m.y), Color(0,0,0));
    win.drawLine(glm::vec2(0.99f, m.y), glm::vec2(1.0f, m.y), Color(0,0,0));

    win.drawLine(glm::vec2(m.x, 0.0f), glm::vec2(m.x, 0.01f), Color(0,0,0));
    win.drawLine(glm::vec2(m.x, 0.99f), glm::vec2(m.x, 1.0f), Color(0,0,0));

    win.update();
  }

  return 0;
}
