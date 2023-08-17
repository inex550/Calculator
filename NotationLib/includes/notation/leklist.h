#ifndef __NOTATION_LEKLIST_H__
#define __NOTATION_LEKLIST_H__

#include <notation/leknode.h>

#include <cstddef>
#include <list>
#include <vector>

namespace nex {
class LekList {
    public:
        void PushBack(const Leksem& node) { nodes_.push_back(node); }

        void PopBack() { nodes_.pop_back(); }

        bool IsEmpty() { return nodes_.empty(); }

        Leksem& LastLek() { return nodes_.back(); }

        const std::vector<Leksem>& GetNodes() const { return nodes_; }

        /**
         * Вычисляет выражение
         * @param X Будет подставлено на место X
         * @returns Значение выражения
         */
        double CalcX(double x);

        // Просто вычисляет выражение
        // Если выражение содержит X, он будет равен 0.0
        double Calc() { return CalcX(0.0); }

        /**
         * Вычисляет значения для графика
         * @param arrX Сырой массив значений X для каждого Y
         * @param arrY Сырой массив Y - результирующий массив
         * @param arrSize Размер сырых массивов
         */
        void CalcGraphic(const double* arrX, double* arrY, size_t arrSize) {
            for (size_t i = 0; i < arrSize; ++i) {
                arrY[i] = CalcX(arrX[i]);
            }
        }

    private:
        std::vector<Leksem> nodes_;
        std::vector<double> numbers_;
    };
}  // namespace nex

#endif  // __NOTATION_LEKLIST_H__
