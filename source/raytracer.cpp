#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <string>

/**
 * 
 * @param argc
 * @param argv first is input path, second ist output path, third to disable window
 * @return 
 */
int main(int argc, char* argv[]) {
    unsigned const width = 600;
    unsigned const height = 600;

    std::cout << "welcome to Raytracer ("<< width<<"x"<<height<<")." <<std::endl;
    Renderer* app = nullptr;
    if (argc>1)
        app = new Renderer(width, height, argv[1]);
    else
        app = new Renderer(width, height);

    std::thread thr([&app]() { app->render(); });

    bool nogui=false;
    for (int i = 0; i < argc; i++) {
        if (string(argv[i]).compare("nogui")==0)
            nogui=true;
    }

    if (!nogui){
        Window win(glm::ivec2(width,height));

        while (!win.shouldClose()) {
          if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
            win.stop();
          }

          glDrawPixels( width, height, GL_RGB, GL_FLOAT
                      , app->colorbuffer().data());

          win.update();
        }
    }
    thr.join();

    delete(app);
    return 0;
}
