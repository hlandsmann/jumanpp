#pragma once
#include <core/analysis/lattice_config.h>
#include <util/string_piece.h>

#include <util/status.hpp>
#include <util/types.hpp>

#include "core/analysis/analysis_result.h"
#include "core/analysis/analyzer.h"
#include "core/analysis/output.h"
#include "core/env.h"
#include "jumandic/shared/jumandic_spec.h"
#include "jumandic_id_resolver.h"
#include "util/fast_printer.h"

namespace jumanpp::jumandic::output {

struct JumandicFields {
  core::analysis::StringField surface;
  core::analysis::StringField pos;
  core::analysis::StringField subpos;
  core::analysis::StringField conjType;
  core::analysis::StringField conjForm;
  core::analysis::StringField baseform;
  core::analysis::StringField reading;
  core::analysis::StringField canonicForm;
  core::analysis::KVListField features;

  auto initialize(const core::analysis::OutputManager& om) -> Status {
    JPP_RETURN_IF_ERROR(om.stringField("surface", &surface));
    JPP_RETURN_IF_ERROR(om.stringField("pos", &pos));
    JPP_RETURN_IF_ERROR(om.stringField("subpos", &subpos));
    JPP_RETURN_IF_ERROR(om.stringField("conjtype", &conjType));
    JPP_RETURN_IF_ERROR(om.stringField("conjform", &conjForm));
    JPP_RETURN_IF_ERROR(om.stringField("baseform", &baseform));
    JPP_RETURN_IF_ERROR(om.stringField("reading", &reading));
    JPP_RETURN_IF_ERROR(om.stringField("canonic", &canonicForm));
    JPP_RETURN_IF_ERROR(om.kvListField("features", &features));
    return Status::Ok();
  }
};

void formatNormalizedFeature(util::io::FastPrinter& p, i32 featureVal);

class JumanFormat : public core::OutputFormat {
  JumandicFields flds;
  util::io::FastPrinter printer;
  core::analysis::AnalysisResult analysisResult;
  core::analysis::AnalysisPath top1;
  core::analysis::NodeWalker walker;
  JumandicIdResolver idResolver;

 public:
  JumanFormat();

  auto initialize(const core::analysis::OutputManager& om) -> Status {
    JPP_RETURN_IF_ERROR(idResolver.initialize(om.dic()));
    return flds.initialize(om);
  }

  auto formatOne(const core::analysis::OutputManager& om,
                 const core::analysis::ConnectionPtr& ptr, bool first) -> bool;
  auto format(const core::analysis::Analyzer& analysis,
              StringPiece comment) -> Status override;
  [[nodiscard]] auto result() const -> StringPiece override {
    return printer.result();
  }
};

inline auto ifEmpty(StringPiece s1, StringPiece s2) -> StringPiece {
  if (s1.size() > 0) {
    return s1;
  }
  return s2;
}

}  // namespace jumanpp::jumandic::output
