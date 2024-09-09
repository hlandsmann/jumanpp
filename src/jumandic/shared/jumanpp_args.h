//
// Created by Arseny Tolmachev on 2017/03/11.
//

#ifndef JUMANPP_JUMANPP_ARGS_H
#define JUMANPP_JUMANPP_ARGS_H

#include <format>
#include <iostream>
#include <ostream>
#include <string>

#include "core/analysis/rnn_scorer.h"
#include "core_config.h"
#include "util/cfg.h"
#include "util/status.hpp"

namespace jumanpp {
namespace jumandic {

enum class OutputType {
  Invalid,
  Version,
  ModelInfo,
  Segmentation,
  Juman,
  Morph,
  FullMorph,
  DicSubset,
  Lattice,
#if defined(JPP_USE_PROTOBUF)
  JumanPb,
  LatticePb,
  FullLatticeDump,
#endif
#if defined(JPP_ENABLE_DEV_TOOLS)
  GlobalBeamPos,
#endif
};

enum class InputType { Raw, PartiallyAnnotated };

struct JumanppConf {
  util::Cfg<std::string> configFile;
  util::Cfg<std::string> modelFile;
  util::Cfg<OutputType> outputType = OutputType::Juman;
  util::Cfg<InputType> inputType = InputType::Raw;
  util::Cfg<std::string> outputFile{"-"};
  util::Cfg<std::vector<std::string>> inputFiles{};
  util::Cfg<std::string> rnnModelFile;
  core::analysis::rnn::RnnInferenceConfig rnnConfig{};
  util::Cfg<std::string> graphvizDir;
  util::Cfg<i32> beamSize = 5;
  util::Cfg<i32> beamOutput = 1;
  util::Cfg<i32> globalBeam = 6;
  util::Cfg<i32> rightBeam = 5;
  util::Cfg<i32> rightCheck = 1;
  util::Cfg<i32> logLevel = 0;
  util::Cfg<i32> autoStep = 0;
  util::Cfg<std::string> segmentSeparator{" "};

  void mergeWith(const JumanppConf& o) {
    configFile.mergeWith(o.configFile);
    std::cout << std::format("configFile: {}\n", configFile.value());
    modelFile.mergeWith(o.modelFile);
    std::cout << std::format("modelfile: {}\n", modelFile.value());
    outputType.mergeWith(o.outputType);
    std::cout << "outputType: " << static_cast<int>(outputType.value()) << "\n";
    outputFile.mergeWith(o.outputFile);
    std::cout << std::format("outputFile: {}\n", outputFile.value());
    inputType.mergeWith(o.inputType);
    std::cout << std::format("inputType: {}\n",
                             static_cast<int>(inputType.value()));
    inputFiles.mergeWith(o.inputFiles);
    std::cout << std::format("inputFiles size: {}\n", inputFiles.value().size());
    rnnModelFile.mergeWith(o.rnnModelFile);
    std::cout << std::format("rnnModelFile: {}\n", rnnModelFile.value());
    rnnConfig.mergeWith(o.rnnConfig);
    std::cout << rnnConfig << "\n";
    graphvizDir.mergeWith(o.graphvizDir);
    std::cout << std::format("graphvizDir: {}\n", graphvizDir.value());
    beamSize.mergeWith(o.beamSize);
    std::cout << std::format("beamSize: {}\n", beamSize.value());
    beamOutput.mergeWith(o.beamOutput);
    std::cout << std::format("beamOutput: {}\n", beamOutput.value());
    globalBeam.mergeWith(o.globalBeam);
    std::cout << std::format("globalBeam: {}\n", globalBeam.value());
    rightBeam.mergeWith(o.rightBeam);
    std::cout << std::format("rightBeam: {}\n", rightBeam.value());
    rightCheck.mergeWith(o.rightCheck);
    std::cout << std::format("rightCheck: {}\n", rightCheck.value());
    logLevel.mergeWith(o.logLevel);
    std::cout << std::format("logLevel: {}\n", logLevel.value());
    autoStep.mergeWith(o.autoStep);
    std::cout << std::format("autoStep: {}\n", autoStep.value());
    segmentSeparator.mergeWith(o.segmentSeparator);
    std::cout << std::format("segmentSeparator: {}\n",
                             segmentSeparator.value());
  }

  friend std::ostream& operator<<(std::ostream& os, const JumanppConf& conf);
};

Status parseCfgFile(StringPiece filename, JumanppConf* conf,
                    i32 recursionDepth = 0);
Status parseArgs(int argc, const char* argv[], JumanppConf* result);

}  // namespace jumandic
}  // namespace jumanpp

#endif  // JUMANPP_JUMANPP_ARGS_H
