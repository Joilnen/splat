#ifndef APP_HPP
#define APP_HPP

#include "camera.hpp"
#include "sorting.hpp"
#include "util.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <utility>
#include <optional>

int main(int argc, char** argv);

namespace splat {

class App {
   public:
    App(std::vector<std::string>& ply_path);
    ~App();
    void run();

    const uint32_t WIDTH = 1280;
    const uint32_t HEIGHT = 720;
    float speed;

   private:
    GLFWwindow* win;
    double time;
    double time_delta;
    void init_window();
    void draw();
    void process_inputs();
    void load_data(const char* ply_path);
    void load_data_(char* ply_path);
    void load_mask();
    void load_shaders();

    std::vector<Gaussian> data = {};
    std::pair<glm::vec3, glm::vec3> bounds;

    std::vector<int> indices = {};
    void sort();
    void async_sort_update();

    uint32_t frame = 0;
    GLuint vertex_buffer;
    GLuint vao;
    GLuint gauss_ssbo;
    GLuint index_ssbo;
    GLuint point_shader;
    GLuint gaussian_shader;
    GLuint halfgaussian_shader;
    GLuint shader;
    size_t num_gaussians;

    Camera cam;
    Sorting sorting;

    std::vector<glm::vec3> mask_points;
    float step_mask {0.0};
    void move_masked();
    void reset_masked();
    bool fstats {true};
    bool fgrays {false};
};
}  // namespace splat

#endif  // APP_HPP
