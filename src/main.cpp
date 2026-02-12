#include <gtkmm.h>
#include <Audio.hpp>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

std::string curdir;

class SFMP : public Gtk::Window {
  public:
  SFMP() : scale(Gtk::ORIENTATION_HORIZONTAL) {
    set_title("SFMP-player");
    set_default_size(700, 500);
    
    auto css = Gtk::CssProvider::create();
    css->load_from_path("style/style.css");
    
    Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    // std::filesystem::create_directories("icons");
    // std::string command = "ffmpeg -i /storage/emulated/0/Music/Telegram/*.mp3 -an -vcodec copy icons/*.jpg 2>/dev/null";
    // system(command.c_str());
    
    Gtk::FileChooserDialog openfold("Select the music folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    openfold.add_button("bruh", Gtk::RESPONSE_CANCEL);
    openfold.add_button("bhai", Gtk::RESPONSE_OK);
    
    int selectfold = openfold.run();
    
    if (selectfold == Gtk::RESPONSE_OK) {
      curdir = openfold.get_filename();;
    }
    
    ico.set_size_request(150, 150);
    ico.get_style_context()->add_class("ico");
    
    fix.add(ico);
    fix.move(ico, 450, 100);
    
    play.set_size_request(50, 50);
    play.set_label("▶");
    play.get_style_context()->add_class("play");
    
    fix.add(play);
    fix.move(play, 490, 300);
    
    scale.set_size_request(250, 100);
    scale.set_range(0.0, 100.0);
    scale.set_value(0.0);
    scale.set_value_pos(Gtk::POS_BOTTOM);
    
    fix.add(scale);
    fix.move(scale, 400, 230);
    
    name.set_size_request(30, 100);
    name.get_style_context()->add_class("name");
    
    fix.add(name);
    fix.move(name, 450, 20);
    
    scroll.set_size_request(350, 500);
    scroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scroll.get_style_context()->add_class("srl");
    
    fix.add(scroll);
    
    list = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5);
    scroll.add(*list);
    
    std::vector<std::string> lablist = {};
    for (const auto& song : std::filesystem::directory_iterator(curdir)) {
      if (song.is_regular_file()) {
        std::string ext = song.path().extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        if (ext == ".mp3" || ext == ".wav") {
          lablist.push_back(song.path().filename().string());
        }
      }
    }
    
    int size = lablist.size();
    std::vector<Gtk::Button*> butlist = {};
    std::vector<sf::Music*> musiclist = {};
    
    for (int i = 0; i < size; i++) {
      size_t idx = i;
      if (lablist[i].length() >= 44) {
        std::string minilab = lablist[i].substr(0, 41) + "...";
        Gtk::Button* music = new Gtk::Button(minilab);
        butlist.push_back(music);
      } else {
        Gtk::Button* music = new Gtk::Button(lablist[i]);
        butlist.push_back(music);
      }
      
      butlist[i]->set_size_request(330, 20);
      list->pack_start(*butlist[i]);
      
      butlist[i]->signal_clicked().connect([this, idx, lablist](){
        play.set_label("▶");
        
        if (mus) {
          mus->stop();
          mus.reset();
        }
        
        std::string curmusic = curdir + "/" + lablist[idx];
        mus = std::make_unique<sf::Music>();
        mus->openFromFile(curmusic);
        
        if (lablist[idx].length() > 20) {
          std::string mininame = lablist[idx].substr(0, 20) + "...";
          name.set_label(mininame);
        } else {
          name.set_label(lablist[idx]);
        }
      });
    }
    
    play.signal_clicked().connect([&](){
      if (click == 0) {
        mus->stop();
        play.set_label("||");
        mus->play();
        click = 1;
      } else if (click == 1) {
        play.set_label("▶");
        mus->pause();
        click = 0;
      }
    }); 
    
    add(fix);
    show_all_children();
  }
  
  Gtk::Fixed fix;
  Gtk::Label ico;
  Gtk::Button play;
  Gtk::Scale scale;
  Gtk::Label name;
  Gtk::ScrolledWindow scroll;
  Gtk::Box* list;
  int click = 0;
  std::unique_ptr<sf::Music> mus;
};

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create(argc, argv, "com.nosokkk.sfmp");
  
  SFMP window;
  return app->run(window);
}