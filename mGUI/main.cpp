#include <elements.hpp>
#include <custom_elements.hpp>

using namespace cycfi::elements;
using namespace blf::custom_elements;

// main window background color
auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto constexpr draw_color = rgba(255, 255, 255, 255);

auto background = box(bkd_color);
auto plot = graph(draw_color, nullptr, nullptr);

auto p5pground = p5::camera(); 

void CustomView(view& v)
{

    


    // all custom content and items you want put right here
    v.content(
        plot,
        background
    );
}


int main(int argc, char** argv)
{
    // run app
    app _app(argc, argv, "Modern GUI", "com.cycfi.mgui");
    window _win(_app.name());
    _win.on_close = [&_app]() { _app.stop(); };

    view view_(_win);

    // All app designs happen here!
    // view_.content(
    //     // lowest layer is at the bottom, add more ontop of it or replace background
    //     plot,
    //     background
    // );

    CustomView(view_);

    _app.run();

    return 0;
}
