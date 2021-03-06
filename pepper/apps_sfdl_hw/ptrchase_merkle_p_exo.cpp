#include <apps_sfdl_hw/ptrchase_merkle_p_exo.h>
#include <apps_sfdl_gen/ptrchase_merkle_cons.h>
#include <common/sha1.h>
#include <storage/configurable_block_store.h>

#pragma pack(push)
#pragma pack(1)

//This file will NOT be overwritten by the code generator, if it already
//exists. make clean will also not remove this file.

ptrchase_merkleProverExo::ptrchase_merkleProverExo() { }

using namespace ptrchase_merkle_cons;

void ptrchase_merkleProverExo::init_exo_inputs(
  const mpq_t* input_q, int num_inputs,
  char *folder_path, HashBlockStore *bs) {
  
}

void ptrchase_merkleProverExo::export_exo_inputs(
  const mpq_t* output_q, int num_outputs,
  char* folder_path, HashBlockStore *bs) {

}

void ptrchase_merkleProverExo::run_shuffle_phase(char *folder_path) {

}

void ptrchase_merkleProverExo::baseline_minimal(void* input, void* output){
  //Run the computation
}

using ptrchase_merkle_cons::NELMS;
using ptrchase_merkle_cons::NDEEP;
void ptrchase_merkleProverExo::baseline(const mpq_t* input_q, int num_inputs, 
      mpq_t* output_recomputed, int num_outputs) {

    uint32_t input[NELMS];

    // read in data
    for(int i=0; i < NELMS; i++) {
        input[i] = mpz_get_ui(mpq_numref(input_q[num_inputs-NELMS+i]));
    }

    // chase pointers
    uint32_t current = input[0];
    for(int i=0; i < NDEEP; i++) {
        current = input[current];
    }

    // set output
    mpq_set_ui(output_recomputed[0], 0, 1);
    mpq_set_ui(output_recomputed[1], current, 1);
}

//Refer to apps_sfdl_gen/ptrchase_merkle_cons.h for constants to use in this exogenous
//check.
bool ptrchase_merkleProverExo::exogenous_check(const mpz_t* input, const mpq_t* input_q,
      int num_inputs, const mpz_t* output, const mpq_t* output_q, int num_outputs, mpz_t prime) {

  bool passed_test = true;
#ifdef ENABLE_EXOGENOUS_CHECKING
  mpq_t *output_recomputed;
  alloc_init_vec(&output_recomputed, num_outputs);
  baseline(input_q, num_inputs, output_recomputed, num_outputs);

  for(int i = 0; i < num_outputs; i++){
    if (mpq_equal(output_recomputed[i], output_q[i]) == 0){
      passed_test = false;
      break;
    }
  }
  clear_vec(num_outputs, output_recomputed);
#else
  gmp_printf("<Exogenous check disabled>\n");
#endif
  return passed_test;
};

#pragma pack(pop)
