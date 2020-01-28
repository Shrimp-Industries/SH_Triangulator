#ifndef SH_TRI_HPP
#define SH_TRI_HPP

#include <vector>

#include "algebra.hpp"  // ALG::

namespace SH{
namespace TRI{
// Input class -----------------------------------------------------------------
    template <typename DataStruct>
    class InData{
    public:
        // Constructors
        InData() = delete;
        InData(DataStruct data):data_(data){};

        // Parsing
        std::vector<typename DataStruct::InnerType> GenerateTriangles(){
            InnerGenerateTriangles();
            return trianglesRaw_;
        };

        // logging
        void PrintData(){
            #ifdef SH_TRI_LOGGING
            for(auto i = 0; i < data_.size(); i++){
                std::cout << "[" << data_.x(i) << ", " << data_.y(i) << "]" << std::endl;
            }
            #endif
        }
    private:
        void InnerGenerateTriangles(){
            // Convert wrapper formatted data to SH::ALG::Points
            ConvertDataToContour();

            for(auto i=0; i<contour_.size()-2; i++){
                auto size = GetShapeSize(contour_[i]);
                std::cout << "Size: " << size << std::endl;

                if(size > 3){
                    ALG::Triangle tr(contour_[i], *(contour_[i].next), *(contour_[i].next->next));
                    std::cout << tr.GetAngle() << std::endl;

                    // Create a midpoint from 1st to 3rd point
                    ALG::Line<typename DataStruct::InnerType> p1p3(*tr.p1, *tr.p3);
                    ALG::Point<typename DataStruct::InnerType> midpoint(p1p3.GetXDiff(), p1p3.GetYDiff(), 0);
                    // Create line going through p2 and midpoint
                    ALG::Line<typename DataStruct::InnerType> line(*tr.p2, midpoint);
                    // Check for collisions with contour
                    CheckForCollisions(line);
                }
            }
        }
        int GetShapeSize(const ALG::LinkedPoint<typename DataStruct::InnerType>& p){
            int counter = 1;
            const ALG::LinkedPoint<typename DataStruct::InnerType>* add = p.next;
            while(&p != add){
                counter++;
                add = add->next;
            }
            return counter;
        }
        bool CheckForCollisions(const ALG::Line<typename DataStruct::InnerType>& line){
            for(auto i=0; i<contour_.size(); i++){
                const ALG::LinkedPoint<typename DataStruct::InnerType>* const first = &contour_[i];
                const ALG::LinkedPoint<typename DataStruct::InnerType>* next = contour_[i].next;
                while(first != next){

                    ALG::Line<typename DataStruct::InnerType> current(*first, *next);
                    ALG::LinkedPoint<typename DataStruct::InnerType> intersection = line.GetIntersectionLinked(current);

                    std::cout << intersection << std::endl;
                    // Check if intersection exists

                    next = next->next;
                }
            }
        }
        void ConvertDataToContour(){
            for(auto i = 0; i<data_.size(); i++){
                contour_.push_back(ALG::LinkedPoint<typename DataStruct::InnerType>(data_.x(i), data_.y(i), i));
                if(i != 0){
                    contour_[i-1].next = &(contour_[i]);
                }
            }
            contour_[0].next = &(contour_[1]);
            contour_[data_.size()-1].next = &(contour_[0]);
        }

        std::vector<typename DataStruct::InnerType> trianglesRaw_;
        DataStruct data_;
        ALG::Contour<typename DataStruct::InnerType> contour_;
    };
// -----------------------------------------------------------------------------

}   // TRI
}   // SH

#endif  // SH_TRI_HPP
