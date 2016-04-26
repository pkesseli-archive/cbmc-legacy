#include <cegis/jsa/converters/replace_operators.h>

namespace
{
class replace_ops_visitort: public expr_visitort
{
  const std::map<std::string, symbol_exprt> replacements;
public:
  virtual void operator()(exprt &expr)
  {

  }
};

std::map<std::string, symbol_exprt> create_pred_replacements(
    const pred_op_idst &pred_ops, const pred_op_idst &result_pred_ops)
{
  //std::map<std::string, size_t> op_to_name = {{1, 'a'}, {3, 'b'}, {5, 'c'}, {7, 'd'}};
  std::map<std::string, symbol_exprt> result;
  return result;
}
}

void replace_pred_ops(goto_programt::instructionst &pred,
    const pred_op_idst &pred_ops, const pred_op_idst &result_pred_ops)
{

}
