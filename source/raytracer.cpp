#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>

int main(int argc, char* argv[])
{
  unsigned const width = 600;
  unsigned const height = 600;
  std::string const filename = "./checkerboard.ppm";

  std::cout << "welcome to Raytracer ("<< width<<"x"<<height<<"). Files are stored into:" <<filename<<std::endl;
  Renderer app = Renderer(width, height, filename);//wie legt man die variable ohne initialisierung an?
  if (argc>0)
    app = Renderer(width, height, filename, argv[1]);

  std::thread thr([&app]() { app.render(); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();

  return 0;
}
