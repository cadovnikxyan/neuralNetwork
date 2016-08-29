#include "neuro.h"

Neuro::Neuro()
{

}

Neuro::link_koefs Neuro::LearnNeuroNet(const list<neurons_line>& src_images)
{
    link_koefs result_koefs;

        size_t neurons_count = src_images.front().size();



        result_koefs.resize(neurons_count);

        for (size_t i = 0; i < neurons_count; ++i) {

            result_koefs[i].resize(neurons_count, 0);

        }



        for (size_t i = 0; i < neurons_count; ++i) {

            for (size_t j = 0; j < i ; ++j ) {

                koef_t val = 0;

                val = accumulate(begin(src_images), end(src_images), koef_t(0.0), [i, j] (koef_t old_val, const neurons_line &image) -> koef_t{

                    return old_val + (image[i] * image[j]);

                });

                result_koefs[i][j] = val;

                result_koefs[j][i] = val;

            }

        }



        return result_koefs;

}


neuro_net_system::neuro_net_system(const Neuro::link_koefs& koefs): _koefs(koefs) {

}

bool neuro_net_system::Execute(Neuro::neurons_line* line) {
    bool value_changed = false;

    Neuro::neurons_line old_values(begin(*line), end(*line));

    Neuro::link_koefs::const_iterator it_koefs = begin(_koefs);

    transform(
                begin(*line),
                end(*line),
                begin(*line),
                [&old_values, &it_koefs, &value_changed] ( Neuro::neuron_state old_value) ->  Neuro::neuron_state {
        Neuro::koef_t tmp_val = inner_product(
                                    begin(old_values),
                                    end(old_values),
                                    begin(*it_koefs++),
                                    Neuro::koef_t(0)
                                    );

        Neuro::neuron_state new_value = (tmp_val > 0 ?  Neuro::UPPER_STATE :  Neuro::LOWER_STATE);
        value_changed = (new_value != old_value) || value_changed;

        return new_value;

    });
    return value_changed;
}

Neuro::neurons_line neuro_net_system::read_neurons_state(const string& file_path, size_t len) {
//    std::ifstream i_file(file_path);

//    size_t i = 0;
//    Neuro::neurons_line result;
//    result.reserve(len);

//    while (i++ < len) {
//        char val;
//        i_file >> val;
//        Neuro::neuron_state state = (val == '0' ? Neuro::LOWER_STATE : Neuro::UPPER_STATE);
//        result.push_back(state);
//    }

//    return result;
}

Neuro::neurons_line* neuro_net_system::operator ()(Neuro::neurons_line* line) {

    bool need_continue = true;
    _steps_processed = 0;

    while (need_continue) {
        need_continue = Execute(line);
        ++_steps_processed;
    }
    return line;
}
