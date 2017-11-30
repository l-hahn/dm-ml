#ifndef _MINING_HPP_
#define _MINING_HPP_

#include <cmath>
#include <vector>

#include "mmatrix.hpp"
#include "meigen.hpp"

namespace data_learning{
  /*---data-mining------------------------------------------------------------*/
    namespace mining{
        template<typename T = double>
        class pca{
            private:
                mmatrix<T> _DataMatrix;
                mmatrix<T> _CovMatrix;
                std::vector< meigen<T> > _Eigens;
                unsigned _EigenNumber;

            public:
                pca(unsigned EigNumber = 0);
                pca(mmatrix<T> && Mat, unsigned EigNumber = 0);
                pca(mmatrix<T> & Mat, unsigned EigNumber = 0);


                void set_matrix(mmatrix<T> && Mat);
                void set_matrix(mmatrix<T> & Mat);

                void eigen_number(unsigned EigNumber);
                unsigned eigen_number();


                mmatrix<T> cov_matrix();
                mmatrix<T> data_matrix();
                std::vector< meigen<T> > eigen();

                mmatrix<T> eigen_spectrum(bool normalise = true);
                mmatrix<T> loadings(unsigned LoadNumber = 0);
                mmatrix<T> loading(unsigned LoadIdx);
                mmatrix<T> principle_components(unsigned CompNumber = 0);
                mmatrix<T> principle_component(unsigned CompIdx);

        };

        template<typename T>
        pca<T>::pca(unsigned EigNumber){
            _EigenNumber = EigNumber;
        }
        template<typename T>
        pca<T>::pca(mmatrix<T> && Mat, unsigned EigNumber):_EigenNumber(EigNumber == 0 ? Mat.col_size() : EigNumber){
            set_matrix(Mat);
        }
        template<typename T>
        pca<T>::pca(mmatrix<T> & Mat, unsigned EigNumber):_EigenNumber(EigNumber == 0 ? Mat.col_size() : EigNumber){
            set_matrix(Mat);
        }

        template<typename T>
        void pca<T>::set_matrix(mmatrix<T> && Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
            _CovMatrix = mmatrix<T>::covariance(Mat);
            _Eigens = mmatrix<T>::eigen(_CovMatrix, _EigenNumber);
        }
        template<typename T>
        void pca<T>::set_matrix(mmatrix<T> & Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
            _CovMatrix = mmatrix<T>::covariance(Mat);
            _Eigens = mmatrix<T>::eigen(_CovMatrix, _EigenNumber);
        }

        template<typename T>
        void pca<T>::eigen_number(unsigned EigNumber){
            _EigenNumber = EigNumber;
        }
        template<typename T>
        unsigned pca<T>::eigen_number(){
            return _EigenNumber;
        }

        template<typename T>
        mmatrix<T> pca<T>::cov_matrix(){
            return _CovMatrix;
        }
        template<typename T>
        mmatrix<T> pca<T>::data_matrix(){
            return _DataMatrix;
        }
        template<typename T>
        std::vector< meigen<T> > pca<T>::eigen(){
            return _Eigens;
        }

        template<typename T>
        mmatrix<T> pca<T>::eigen_spectrum(bool normalise){
            mmatrix<T> EigSpec = mmatrix<T>(1,_EigenNumber);
            T Sum = 0;
            for(unsigned i = 0; i < _EigenNumber; i++){
                EigSpec[0][i] = _Eigens[i].value();
                Sum += _Eigens[i].value();
            }
            if(normalise){
                std::transform(EigSpec[0].begin(), EigSpec[0].end(), EigSpec[0].begin(), [Sum](T & Val){
                    return Val/Sum;
                });
            }
            return EigSpec;
        }
        template<typename T>
        mmatrix<T> pca<T>::loadings(unsigned LoadNumber){
            if(LoadNumber == 0){
                LoadNumber = _EigenNumber;
            }
            mmatrix<T> Loadings = mmatrix<T>();
            for(meigen<T> Eigen : _Eigens){
                Loadings.push_back(Eigen.vector());
            }
            return Loadings;
        }
        template<typename T>
        mmatrix<T> pca<T>::loading(unsigned LoadIdx){
            return _Eigens[LoadIdx].vector();
        }
        template<typename T>
        mmatrix<T> pca<T>::principle_components(unsigned CompNumber){
            if(CompNumber == 0){
                CompNumber = _EigenNumber;
            }
            mmatrix<T> PrinComp = _DataMatrix*loadings().transposition();
            return PrinComp;
        }
        template<typename T>
        mmatrix<T> pca<T>::principle_component(unsigned CompIdx){
            return _DataMatrix*_Eigens[CompIdx].vector().transposition();
        }

      /*----------------------------------------------------------------------*/
        template<typename T = double>
        class mds{
            private:
                mmatrix<T> _DataMatrix;
                std::vector< meigen<T> > _Eigens;
                unsigned _EigenNumber;

            public:
                mds(unsigned EigNumber = 0);
                mds(mmatrix<T> && Mat, unsigned EigNumber = 0);
                mds(mmatrix<T> & Mat, unsigned EigNumber = 0);

                void set_matrix(mmatrix<T> && Mat);
                void set_matrix(mmatrix<T> & Mat);
        };


      /*----------------------------------------------------------------------*/
        template<typename T = double>
        class sammon{
            private:
                mmatrix<T> _DataMatrix;
                std::vector< meigen<T> > _Eigens;
                unsigned _EigenNumber;

            public:
                sammon(unsigned EigNumber = 0);
                sammon(mmatrix<T> && Mat, unsigned EigNumber = 0);
                sammon(mmatrix<T> & Mat, unsigned EigNumber = 0);

                void set_matrix(mmatrix<T> && Mat);
                void set_matrix(mmatrix<T> & Mat);
        };

        class kernelreg{

        };

    };
};
#endif