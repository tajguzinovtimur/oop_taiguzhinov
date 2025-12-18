#include "Figure.hpp"


template class Figure<int>;
template class Figure<float>;
template class Figure<double>;


template<ScalarType T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
    figure.print(os);
    return os;
}

template<ScalarType T>
std::istream& operator>>(std::istream& is, Figure<T>& figure) {
    figure.input(is);
    return is;
}

template<ScalarType T>
Figure<T>::operator double() const {
    return area();
}

template<ScalarType T>
const std::vector<std::unique_ptr<Point<T>>>& Figure<T>::getVertices() const {
    return vertices;
}

template<ScalarType T>
void Figure<T>::printVertices(std::ostream& os) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        os << "Vertex " << i + 1 << ": " << *vertices[i];
        if (i != vertices.size() - 1) os << ", ";
    }
}