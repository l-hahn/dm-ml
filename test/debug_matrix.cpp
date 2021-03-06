/*===Libraries================================================================*/
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <omp.h>

#include "../src/mmatrix.hpp"
#include "../src/meigen.hpp"

/*===Classes-Structurres======================================================*/

/*===Variables================================================================*/

/*===Prototypes===============================================================*/
void constructors();
void memory();
void push_back();
void operators();
void static_operations();
void static_norms(); 


/*===Main=====================================================================*/
int main(){
    mmatrix<double>::thread(omp_get_max_threads());
    constructors();
    memory();
    push_back();
    operators();
    static_operations();
    static_norms();
}

/**
 * Check if constructors are working and modification is still possible.
 */
void constructors(){
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tA) Matrix Constructors \t\t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    mmatrix<double> MatrixHc = {{1,2,3},{4,5,6},{7,8,9}};
    std::cout << "MatrixHc = {{1,2,3},{4,5,6},{7,8,9}}: \n" << MatrixHc.to_string() << std::endl << std::endl; 
    mmatrix<double> MatrixHcV = {10,11,12};
    std::cout << "MatrixHcV = {1,2,3}: \n" << MatrixHcV.to_string() << std::endl << std::endl; 
    mmatrix<double> MatrixDef;
    std::cout << "MatrixDef \n" << MatrixDef.to_string() << std::endl; 
    mmatrix<double> MatrixDim1(MatrixHc.size());
    std::cout << "MatrixDim1(MatrixHc.size()) \n" << MatrixDim1.to_string() << std::endl << std::endl;  
    mmatrix<double> MatrixDim2(MatrixHc.row_size(),MatrixHc.col_size());
    std::cout << "MatrixDim2(MatrixHc.row_size(),MatrixHc.col_size()) \n" << MatrixDim2.to_string() << std::endl << std::endl;   
    mmatrix<double> MatrixVec(MatrixHcV[0]);
    std::cout << "MatrixVec(MatrixHcV[0]): \n" << MatrixVec.to_string() << std::endl << std::endl;   
    mmatrix<double> MatrixVecVec(MatrixHc.vector_matrix());
    std::cout << "MatrixVecVec(MatrixHc.vetor_matrix()): \n" << MatrixVecVec.to_string() << std::endl << std::endl;
    mmatrix<double> MatrixCopy(MatrixHc);
    std::cout << "MatrixCopy(MatrixHcV): \n" << MatrixCopy.to_string() << std::endl << std::endl;

    MatrixDef.push_back(MatrixHcV[0]);
    for(auto Vec : MatrixHc){
        MatrixDef.push_back(Vec);
    }
    std::cout << "MatrixDef[i] = MatrixHc[i] for all i: \n" << MatrixCopy.to_string() << std::endl << std::endl;

    for(std::size_t i = 0; i < MatrixHc.row_size(); i++){
        for(std::size_t j = 0; j < MatrixHc.col_size(); j++){
            assert(MatrixDim1[i][j] == 0.0);
            MatrixDim1[i][j] = MatrixHc[i][j];
            MatrixDim2[i][j] = MatrixHc[i][j];
        }
    }
    std::cout << "MatrixDim1,2[i][j] = MatrixHc[i][j] for all i,j: \n" << MatrixDim1.to_string() << std::endl << std::endl;
}

void memory(){
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tB) Matrix Memory Functions \t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    mmatrix<double> MatrixHc = {{1,2,3},{4,5,6},{7,8,9}};
    mmatrix<double> Matrix0;
    std::cout << "MatrixHc: \n" << MatrixHc.to_string() << std::endl << std::endl;   
    std::cout << "Matrix0: \n" << Matrix0.to_string() << std::endl << std::endl;

    Matrix0.resize(MatrixHc.size(),1);
    std::cout << "Matrix0.resize(MatrixHc.size(),1): \n" << Matrix0.to_string() << std::endl << std::endl;
    Matrix0.resize(MatrixHc.row_size()*2,MatrixHc.col_size()*2,2);
    std::cout << "Matrix0.resize(MatrixHc.row_size()*2,MatrixHc.col_size()*2,2): \n" << Matrix0.to_string() << std::endl << std::endl;
    Matrix0.resize(MatrixHc.row_size()-1,MatrixHc.col_size()-1,3);
    std::cout << "Matrix0.resize(MatrixHc.row_size()-1,MatrixHc.col_size()-2,3): \n" << Matrix0.to_string() << std::endl << std::endl;
    Matrix0.reserve(10);
    std::cout << "Matrix0.reserve(10): \n" << Matrix0.to_string() << std::endl << std::endl;
    Matrix0.resize(10,-1.337);
    std::cout << "Matrix0.resize(10,-1.337): \n" << Matrix0.to_string() << std::endl << std::endl;

}

void push_back(){
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tC) Matrix Matrix/Vector push_back \t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    mmatrix<double> MatrixDef;
    std::vector<double> VectorVec = {1,2,3};
    std::vector< std::vector<double> > VectorVecVec = {{1,2,3},{4,5,6},{7,8,9}};

    std::cout << "MatrixDef: \n" << MatrixDef.to_string() << std::endl << std::endl;   
    std::cout << "VectorVec: \n1 2 3" << std::endl << std::endl;   
    std::cout << "VectorVecVec: \n1 2 3\n4 5 6\n7 8 9" << std::endl << std::endl;   
    

    MatrixDef.push_back(VectorVecVec);
    std::cout << "MatrixDef.push_back(VectorVecVec): \n" << MatrixDef.to_string() << std::endl << std::endl;
    MatrixDef.push_back_row(VectorVec);
    std::cout << "MatrixDef.push_back_row(VectorVec): \n" << MatrixDef.to_string() << std::endl << std::endl;
    MatrixDef = (MatrixDef.transposition()*MatrixDef);
    MatrixDef.push_back_col(VectorVecVec[2]);
    std::cout << "(MatrixDef'*MatrixDef).push_back_col(VectorVecVec[2]): \n" << MatrixDef.to_string() << std::endl << std::endl;
}

void operators(){
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tD) Matrix Matrix/Vector Operators \t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;
    mmatrix<double> MatrixHc = {{1,2,3},{4,5,6},{7,8,9}};
    mmatrix<double> MatrixHcV = {10,11,12};
    mmatrix<double> MatrixDef;
    mmatrix<double> MatrixDim(MatrixHc.size());
    mmatrix<double> MatrixVec(MatrixHcV[0]);
    mmatrix<double> MatrixCopy(MatrixHc);

    std::vector<double> VectorVec = {1,2,3};

    MatrixDef.push_back(MatrixHcV[0]);
    for(auto Vec : MatrixHc){
        MatrixDef.push_back(Vec);
    }
    
    for(std::size_t i = 0; i < MatrixHc.row_size(); i++){
        for(std::size_t j = 0; j < MatrixHc.col_size(); j++){
            assert(MatrixDim[i][j] == 0.0);
            MatrixDim[i][j] = MatrixHc[i][j];
        }
    }

    std::cout << "MatrixCopy: \n" << MatrixCopy.to_string() << std::endl << std::endl;   
    std::cout << "MatrixDim: \n" << MatrixDim.to_string() << std::endl << std::endl;   
    std::cout << "MatrixHc: \n" << MatrixHc.to_string() << std::endl << std::endl;   
    std::cout << "MatrixDef: \n" << MatrixDef.to_string() << std::endl << std::endl;
    std::cout << "MatrixHcV: \n" << MatrixHcV.to_string() << std::endl << std::endl;
    std::cout << "MatrixVec: \n" << MatrixVec.to_string() << std::endl << std::endl;
    std::cout << "VectorVec: \n" << (char)((char)VectorVec[0]+'0') << " " << (char)((char)VectorVec[1]+'0') << " " << (char)((char)VectorVec[2]+'0') << std::endl << std::endl;



    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tD1) Matrix */ Matrix Multiplication\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy = MatrixCopy * MatrixDim;
    std::cout << "MatrixCopy = MatrixCopy * MatrixDim: \n" << MatrixCopy.to_string() << std::endl << std::endl;   
    MatrixCopy = MatrixCopy * MatrixHc;
    std::cout << "MatrixCopy = MatrixCopy * MatrixHc: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy * MatrixVec.transposition();
    std::cout << "MatrixCopy = MatrixCopy * MatrixVec': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy * MatrixCopy.transposition()/1000000;
    std::cout << "MatrixCopy = MatrixCopy * MatrixCopy'/1000000: \n" << MatrixCopy.to_string() << std::endl << std::endl;




    MatrixCopy = mmatrix<double>(MatrixHc);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tD2) Matrix */= Matrix Multiplication\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy *= MatrixDim;
    std::cout << "MatrixCopy *= MatrixDim: \n" << MatrixCopy.to_string() << std::endl << std::endl;   
    MatrixCopy *= MatrixHc;
    std::cout << "MatrixCopy *= MatrixHc: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy *= MatrixVec.transposition();
    std::cout << "MatrixCopy *= MatrixVec': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy *= MatrixCopy.transposition()/1000000;
    std::cout << "MatrixCopy *= MatrixCopy'/1000000: \n" << MatrixCopy.to_string() << std::endl << std::endl;




    MatrixCopy = mmatrix<double>(MatrixHc);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tD3) Matrix +- Matrix Addition\t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy = MatrixCopy*MatrixCopy.transposition() + MatrixCopy*MatrixCopy.transposition();
    std::cout << "MatrixCopy = MatrixCopy*MatrixCopy' + MatrixCopy*MatrixCopy': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy+MatrixHc;
    std::cout << "MatrixCopy = MatrixCopy+MatrixHc: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy*MatrixVec.transposition()+MatrixVec.transposition();
    std::cout << "MatrixCopy = MatrixCopy*MatrixVec' + MatrixVec': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy.transposition()-MatrixVec;
    std::cout << "MatrixCopy = MatrixCopy'-MatrixVec: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy.transposition()*MatrixVec - MatrixHc;
    std::cout << "MatrixCopy = MatrixCopy'*MatrixVec - MatrixHc: \n" << MatrixCopy.to_string() << std::endl << std::endl;




    MatrixCopy = mmatrix<double>(MatrixHc);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tD4) Matrix +-= Matrix Addition\t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy += MatrixCopy.transposition();
    std::cout << "MatrixCopy += MatrixCopy': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy -= MatrixCopy*MatrixCopy.transposition();
    std::cout << "MatrixCopy -= MatrixCopy*MatrixCopy': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy += MatrixCopy*MatrixCopy;
    std::cout << "MatrixCopy += MatrixCopy*MatrixCopy: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy -= MatrixCopy.transposition()*MatrixCopy.transposition();
    std::cout << "MatrixCopy -= MatrixCopy'*MatrixCopy': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    
    


    MatrixCopy = mmatrix<double>(MatrixHc);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tD5) Matrix * Vector Multiplication\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy = MatrixCopy * MatrixVec.transposition();
    std::cout << "MatrixCopy = MatrixCopy * MatrixVec': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy * MatrixVec;
    std::cout << "MatrixCopy = MatrixCopy * MatrixVec: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy * MatrixDef.transposition();
    std::cout << "MatrixCopy = MatrixCopy * MatrixDef': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy.transposition()*MatrixHc.transposition();
    std::cout << "MatrixCopy = MatrixCopy' * MatrixHc': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixHc*MatrixVec.transposition()*VectorVec;
    std::cout << "MatrixHc = (MatrixCopy*MatrixVec) * VectorVec: \n" << MatrixCopy.to_string() << std::endl << std::endl;



    MatrixCopy = mmatrix<double>(MatrixHc);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tD6) Matrix *= Vector Multiplication\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy *= MatrixVec.transposition();
    std::cout << "MatrixCopy *= MatrixVec': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy *= VectorVec;
    std::cout << "MatrixCopy *= VectorVec: \n" << MatrixCopy.to_string() << std::endl << std::endl;



    MatrixCopy = mmatrix<double>(MatrixHc);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tD7) Matrix *= -or- * Matrix Entry-Multiplication\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy = MatrixCopy.entry_mult(MatrixCopy.transposition());
    std::cout << "MatrixCopy = MatrixCopy .* MatrixCopy': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy.vec_entry_mult(VectorVec);
    std::cout << "MatrixCopy = MatrixCopy .* VectorVec: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy.equal_entry_mult(MatrixCopy.transposition());
    std::cout << "MatrixCopy .*= MatrixCopy': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy.equal_vec_entry_mult(VectorVec);
    std::cout << "MatrixCopy .*= VectorVec: \n" << MatrixCopy.to_string() << std::endl << std::endl;
}

void static_operations(){
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tE) Static Matrix Operations\t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    mmatrix<double> MatrixHc = {{1,2,3},{4,5,6},{7,8,9}};
    mmatrix<double> MatrixVec = {1,2,3};
    mmatrix<double> MatrixCopy(MatrixVec);

    std::function<double (double)> function;
    std::function<mmatrix<double> (mmatrix<double>)> mat_function;

    std::cout << "MatrixHc: \n" << MatrixHc.to_string() << std::endl << std::endl;    
    std::cout << "MatrixVec: \n" << MatrixVec.to_string() << std::endl << std::endl;    
    std::cout << "MatrixCopy: \n" << MatrixCopy.to_string() << std::endl << std::endl;    


    MatrixCopy = mmatrix<double>::repmat(MatrixCopy,3,1);
    std::cout << "MatrixCopy = mmatrix::repmat(MatrixCopy,3,1): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = mmatrix<double>::repmat(mmatrix<double>(MatrixCopy),3,3);
    std::cout << "MatrixCopy = mmatrix::repmat(MatrixCopy,3,1): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    function = [](double Val){return Val*Val;};
    mmatrix<double>::transform(MatrixHc, function);
    std::cout << "std::function<T (T)> function = [](double Val){return Val*Val}" << std::endl;
    std::cout << "mmatrix::transform(MatrixHc, function): \n" << MatrixHc.to_string() << std::endl << std::endl;
    mat_function = [](mmatrix<double> Mat){
        for(auto iter = Mat.begin(); iter != Mat.end(); iter++){
            for(auto jter = iter->begin(); jter != iter->end(); jter++){
                *jter = sqrt(*jter);
            }
        }
        return Mat;
    };
    mmatrix<double>::transform(MatrixHc,mat_function);
    std::cout << "std::function<T (T)> mat_function = [](mmatrix<double> Val){...sqrt for each value...}" << std::endl;
    std::cout << "mmatrix::transform(MatrixHc, mat_function): \n" << MatrixHc.to_string() << std::endl << std::endl;
    mmatrix<double>::transform(MatrixHc.begin(),MatrixHc.end(),function);
    std::cout << "mmatrix::transform(MatrixHc.begin(),MatrixHc.end(), function): \n" << MatrixHc.to_string() << std::endl << std::endl;
    std::cout << "mmatrix::max(MatrixHc): \n" << mmatrix<double>::max(MatrixHc) << std::endl << std::endl;
    std::cout << "mmatrix::min(MatrixHc): \n" << mmatrix<double>::min(MatrixHc) << std::endl << std::endl;
    std::cout << "mmatrix::sum(MatrixHc): \n" << mmatrix<double>::sum(MatrixHc) << std::endl << std::endl;
    MatrixCopy = mmatrix<double>::maxs(MatrixHc);
    std::cout << "MatrixCopy = mmatrix::maxs(MatrixHc): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = mmatrix<double>::mins(MatrixHc);
    std::cout << "MatrixCopy = mmatrix::mins(MatrixHc): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = mmatrix<double>::sums(MatrixHc);
    std::cout << "MatrixCopy = mmatrix::sums(MatrixHc): \n" << MatrixCopy.to_string() << std::endl << std::endl;

    MatrixCopy = mmatrix<double>::covariance(MatrixHc);
    std::cout << "MatrixCopy = mmatrix::covariance(MatrixHc): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = mmatrix<double>::gramian(MatrixHc);
    std::cout << "MatrixCopy = mmatrix::gramian(MatrixHc): \n" << MatrixCopy.to_string() << std::endl << std::endl;
}

void static_norms(){
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tF) Static Normalisation Operations\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    mmatrix<double> MatrixHc = {{1,2,3},{4,5,6},{7,8,9}};
    mmatrix<double> MatrixVec = {1,2,3};
    mmatrix<double> MatrixCopy(MatrixVec);
    double Norm;

    std::cout << "MatrixHc: \n" << MatrixHc.to_string() << std::endl << std::endl;    
    std::cout << "MatrixVec: \n" << MatrixVec.to_string() << std::endl << std::endl;    
    std::cout << "MatrixCopy: \n" << MatrixCopy.to_string() << std::endl << std::endl;    


    MatrixCopy = mmatrix<double>::vector_norms(MatrixHc,1);
    std::cout << "MatrixCopy = mmatrix::vector_norms(MatrixHc,1): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = mmatrix<double>::vector_norms(MatrixHc,2);
    std::cout << "MatrixCopy = mmatrix::vector_norms(MatrixHc,2): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = mmatrix<double>::vector_norms(MatrixHc,200);
    std::cout << "MatrixCopy = mmatrix::vector_norms(MatrixHc,200): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    
    Norm = mmatrix<double>::vector_norm(MatrixCopy,1);
    std::cout << "Norm = mmatrix::vector_norm(MatrixCopy,1): \n" << Norm << std::endl << std::endl;
    Norm = mmatrix<double>::vector_norm(MatrixCopy,2);
    std::cout << "Norm = mmatrix::vector_norm(MatrixCopy,2): \n" << Norm << std::endl << std::endl;
    Norm = mmatrix<double>::vector_norm(MatrixCopy,200);
    std::cout << "Norm = mmatrix::vector_norm(MatrixCopy,200): \n" << Norm << std::endl << std::endl;
    
    MatrixCopy = mmatrix<double>::vector_norms(MatrixHc,mmatrix<double>::euclids);
    std::cout << "MatrixCopy = mmatrix::vector_norms(MatrixHc,mmatrix::euclids): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = mmatrix<double>::vector_norms(MatrixHc,mmatrix<double>::taxicaps);
    std::cout << "MatrixCopy = mmatrix::vector_norms(MatrixHc,mmatrix::taxicaps): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    

    Norm = mmatrix<double>::vector_norm(MatrixCopy,mmatrix<double>::taxicap);
    std::cout << "Norm = mmatrix::vector_norm(MatrixCopy,mmatrix::taxicap): \n" << Norm << std::endl << std::endl;
    Norm = mmatrix<double>::vector_norm(MatrixCopy,mmatrix<double>::euclid);
    std::cout << "Norm = mmatrix::vector_norm(MatrixCopy,mmatrix::euclid): \n" << Norm << std::endl << std::endl;


    MatrixCopy = MatrixHc*2;
    std::cout << "MatrixHc: \n" << MatrixHc.to_string() << std::endl << std::endl;       
    std::cout << "MatrixCopy: \n" << MatrixCopy.to_string() << std::endl << std::endl;    


    MatrixCopy = mmatrix<double>::vectorwise_distance(MatrixCopy,MatrixHc,1);
    std::cout << "MatrixCopy = mmatrix::vectorwise_distance(MatrixCopy,MatrixHc,1): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = mmatrix<double>::vectorwise_distance(MatrixCopy,MatrixHc,1);
    std::cout << "MatrixCopy = mmatrix::vectorwise_distance(MatrixCopy,MatrixHc,1): \n" << MatrixCopy.to_string() << std::endl << std::endl;
    Norm = mmatrix<double>::distance(MatrixCopy,MatrixHc,2);  
    std::cout << "Norm = mmatrix::distance(MatrixCopy,MatrixHc,2): \n" << Norm << std::endl << std::endl;

    std::vector< meigen<double> > Eigens = mmatrix<double>::eigen(MatrixHc,MatrixHc.col_size(),mmatrix<double>::euclid);
    std::cout << "Eigen = mmatrix::eigen(MatrixHc,MatrixHc.col_size(),mmatrix::euclid):" << std::endl;
    int Ctr = 0;
    for(auto & Eigen : Eigens){
        std::cout << "\tEigen.vector() " << Ctr << ": \n\t" << Eigen.vector().to_string() << std::endl;
        std::cout << "\tEigen.value() " << Ctr++ << " \n\t" << Eigen.value() << std::endl;
    }
    std::cout << std::endl;
}