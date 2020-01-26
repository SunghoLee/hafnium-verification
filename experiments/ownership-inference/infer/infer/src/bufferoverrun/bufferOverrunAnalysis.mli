(*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *)

open! IStd
module CFG = ProcCfg.NormalOneInstrPerNode

type invariant_map

val cached_compute_invariant_map : Summary.t -> Tenv.t -> Typ.IntegerWidths.t -> invariant_map

val extract_pre : CFG.Node.id -> invariant_map -> BufferOverrunDomain.Mem.t option

val extract_post : CFG.Node.id -> invariant_map -> BufferOverrunDomain.Mem.t option

val extract_state :
  CFG.Node.id -> invariant_map -> BufferOverrunDomain.Mem.t AbstractInterpreter.State.t option

val do_analysis : Callbacks.proc_callback_t
