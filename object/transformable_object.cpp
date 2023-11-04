//
// Created by rc_marty on 3.11.23.
//

#include "transformable_object.h"
#include <utility>
#include <stdexcept>


void Transformable_object::render(double delta_time) {
    if (transform_operations) {
        transform_operations->tick(delta_time);
        Matrix_transformed = transform_operations->get_matrix(Matrix);
        //printf("[DEBUG] Renderable_object: %s,Matrix:\n%s\n", this->name.c_str(), transform_operations->print_matrix(mat).c_str());
    }
    //printf("[DEBUG] Renderable_object: ,Matrix:\n%s\n", transform_operations->print_matrix(Matrix_transformed).c_str());
}


Transformable_object Transformable_object::set_transform_operations(std::shared_ptr<Transforms::Transform> transform_operations, bool static_tr) {
    this->transform_operations = transform_operations;
    if (static_tr)
        Matrix = transform_operations->get_matrix(Matrix);
    return *this;
}