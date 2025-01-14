// Copyright 2021-2023 Lawrence Livermore National Security, LLC and other ExaCA Project Developers.
// See the top-level LICENSE file for details.
//
// SPDX-License-Identifier: MIT

#ifndef GA_UTIL_HPP
#define GA_UTIL_HPP

#include "ExaCA.hpp"

#include <Kokkos_Core.hpp>

#ifdef ExaCA_ENABLE_JSON
#include <nlohmann/json.hpp>
#endif

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

int FindTopOrBottom(int ***LayerID, int XLow, int XHigh, int YLow, int YHigh, int nz, int L, std::string HighLow);

// These are used in reading/parsing ExaCA microstructure data
void ParseLogFile(std::string LogFile, int &nx, int &ny, int &nz, double &deltax, int &NumberOfLayers,
                  std::vector<double> &XYZBounds, std::string &RotationFilename, std::string &EulerAnglesFilename,
                  std::string &RGBFilename, bool OrientationFilesInInput);
void ReadASCIIField(std::ifstream &InputDataStream, int nx, int ny, int nz, ViewI3D_H FieldOfInterest);
void ReadBinaryField(std::ifstream &InputDataStream, int nx, int ny, int nz, ViewI3D_H FieldOfInterest,
                     std::string FieldName);
void InitializeData(std::string MicrostructureFile, int nx, int ny, int nz, ViewI3D_H GrainID, ViewI3D_H LayerID);
void CheckInputFiles(std::string &LogFile, std::string MicrostructureFile, std::string &RotationFilename,
                     std::string &RGBFilename, std::string &EulerAnglesFilename);
double convertToMicrons(double deltax, std::string RegionType);
double convertToCells(double deltax, std::string RegionType);
std::vector<int> getRepresentativeRegionGrainIDs(ViewI3D_H GrainID, const int XLow, const int XHigh, const int YLow,
                                                 const int YHigh, const int ZLow, const int ZHigh,
                                                 const int RepresentativeRegionSize);
std::vector<int> getUniqueGrains(const std::vector<int> GrainIDVector, int &NumberOfGrains);
ViewI_H getOrientationHistogram(int NumberOfOrientations, ViewI3D_H GrainID, ViewI3D_H LayerID, int XMin, int XMax,
                                int YMin, int YMax, int ZMin, int ZMax);
ViewI_H getOrientationHistogram(int NumberOfOrientations, std::vector<int> GrainIDVector,
                                int RepresentativeRegionSize_Cells);
std::vector<float> getGrainSizes(const std::vector<int> GrainIDVector, const std::vector<int> UniqueGrainIDVector,
                                 const int NumberOfGrains, double deltax, std::string RegionType);
void calcGrainExtent(std::vector<float> &GrainExtent, ViewI3D_H GrainID, const std::vector<int> UniqueGrainIDVector,
                     std::vector<float> GrainSizeVector, const int NumberOfGrains, const int XLow, const int XHigh,
                     const int YLow, const int YHigh, const int ZLow, const int ZHigh, std::string Direction,
                     double deltax, std::string RegionType);
std::vector<float> getGrainMisorientation(std::string Direction, ViewF_H GrainUnitVector,
                                          std::vector<int> UniqueGrainIDVector, int NumberOfOrientations,
                                          int NumberOfGrains);
void calcBuildTransAspectRatio(std::vector<float> &BuildTransAspectRatio, std::vector<float> GrainExtentX,
                               std::vector<float> GrainExtentY, std::vector<float> GrainExtentZ, int NumberOfGrains);
std::vector<float> getIPFZColor(int Color, std::vector<int> UniqueGrainIDVector, int NumberOfOrientations,
                                ViewF_H GrainRGBValues, int NumberOfGrains);
template <typename ReturnType, typename FirstType, typename SecondType>
ReturnType DivideCast(FirstType Int1, SecondType Int2) {
    return static_cast<ReturnType>(Int1) / static_cast<ReturnType>(Int2);
}

#endif
