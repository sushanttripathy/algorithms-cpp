//
// Created by sushant on 6/13/18.
//

#ifndef ALGORITHMS_ARRAY_ACTORS_H
#define ALGORITHMS_ARRAY_ACTORS_H

namespace KAGU{
    template <typename X>
    class array_actor_2d{
    public:
        array_actor_2d(void *data){
            this->data = data;
        }

        ~array_actor_2d();

        virtual X get_element(int row, int column) = 0;
        virtual int size() = 0;
        virtual int rows() = 0;
        virtual int columns() = 0;

        class array_1d_proxy{
        public:
            array_1d_proxy(int row, array_actor_2d<X> *parent){
                this->row = row;
                this->parent = parent;
            }

            X operator [](int index){
                return this->parent->get_element(this->row, index);
            }

        protected:
            int row;
            array_actor_2d<X> *parent;
        };

        array_1d_proxy operator [](int index){
            return array_1d_proxy(index, this);
        }

    protected:
        void *data;
    };

}

#endif //ALGORITHMS_ARRAY_ACTORS_H
