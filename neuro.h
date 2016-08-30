#ifndef NEURO_H
#define NEURO_H
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class Neuro
{
     public:
        enum neuron_state {LOWER_STATE=-1,UPPER_STATE=1};
        typedef float koef_t;
        typedef vector<neuron_state> neurons_line;
        typedef vector<vector<koef_t> > link_koefs;


        Neuro();
        link_koefs LearnNeuroNet (const list<neurons_line> &src_images);
};
class  neuro_net_system {
    public:
        const  Neuro::link_koefs &_koefs;
        size_t _steps_processed;

        neuro_net_system(const Neuro::link_koefs &koefs);

        bool Execute(Neuro::neurons_line *line);

        Neuro::neurons_line* recognize ( Neuro::neurons_line *line);
};
class neurons_line_print_descriptor {
    public:
        const Neuro::neurons_line &_line;
        const size_t _width;
        const size_t _height;

        neurons_line_print_descriptor (const Neuro::neurons_line &line, size_t width, size_t height);

};


#endif // NEURO_H
