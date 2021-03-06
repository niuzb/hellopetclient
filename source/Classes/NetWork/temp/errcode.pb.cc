// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: errcode.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "errcode.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::EnumDescriptor* ol_errcode_t_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* db_errcode_t_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_errcode_2eproto() {
  protobuf_AddDesc_errcode_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "errcode.proto");
  GOOGLE_CHECK(file != NULL);
  ol_errcode_t_descriptor_ = file->enum_type(0);
  db_errcode_t_descriptor_ = file->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_errcode_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_errcode_2eproto() {
}

void protobuf_AddDesc_errcode_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rerrcode.proto*\250\007\n\014ol_errcode_t\022\022\n\014oler"
    "r_decode\020\241\215\006\022\027\n\021olerr_invalid_req\020\242\215\006\022\031\n"
    "\023olerr_invalid_dbrsp\020\243\215\006\022\027\n\021olerr_multi_"
    "login\020\261\333\006\022\031\n\023olerr_role_creating\020\262\333\006\022\030\n\022"
    "olerr_no_such_role\020\263\333\006\022\035\n\027olerr_can_tran"
    "sfer_next\020\264\333\006\022\034\n\026olerr_not_enough_level\020"
    "\265\333\006\022\036\n\030olerr_not_enough_diamond\020\266\333\006\022\033\n\025o"
    "lerr_not_enough_coin\020\267\333\006\022\036\n\030olerr_not_en"
    "ough_exploit\020\270\333\006\022\037\n\031olerr_buy_times_logi"
    "c_err\020\270\333\006\022$\n\036olerr_not_enough_explore_ti"
    "mes\020\271\333\006\022\036\n\030olerr_nofound_explore_id\020\272\333\006\022"
    "\033\n\025olerr_nofound_item_id\020\312\251\007\022\031\n\023olerr_ex"
    "ist_item_id\020\313\251\007\022\033\n\025olerr_not_enough_item"
    "\020\314\251\007\022\027\n\021olerr_invalid_pos\020\315\251\007\022\025\n\017olerr_e"
    "xist_pos\020\316\251\007\022\033\n\025olerr_invalid_item_id\020\317\251"
    "\007\022\030\n\022olerr_invalid_hole\020\320\251\007\022&\n olerr_not"
    "_enough_reset_gam_times\020\321\251\007\022\035\n\027olerr_ope"
    "n_hole_seq_err\020\322\251\007\022\032\n\024olerr_not_enough_p"
    "os\020\323\251\007\022\035\n\027olerr_warm_sport_lv_max\020\324\251\007\022\033\n"
    "\025olerr_manor_opt_error\020\325\251\007\022\036\n\030olerr_not_"
    "clear_manor_cd\020\326\251\007\022!\n\033olerr_enter_manor_"
    "times_max\020\327\251\007\022\037\n\031olerr_old_shop_items_li"
    "st\020\336\251\007\022\"\n\034olerr_invalid_buy_item_index\020\337"
    "\251\007\022\036\n\030olerr_has_buy_item_index\020\340\251\007*\350\004\n\014d"
    "b_errcode_t\022\016\n\ndberr_succ\020\000\022\021\n\013dberr_dbm"
    "em\020\251\242\014\022\021\n\013dberr_dbsys\020\252\242\014\022\021\n\013dberr_dbnet"
    "\020\253\242\014\022\022\n\014dberr_no_cmd\020\254\242\014\022\024\n\016dberr_protol"
    "en\020\255\242\014\022\021\n\013dberr_range\020\256\242\014\022\023\n\rdberr_setfl"
    "ag\020\257\242\014\022\020\n\ndberr_data\020\260\242\014\022\020\n\ndberr_enum\020\261"
    "\242\014\022\030\n\022dberr_sendprotolen\020\262\242\014\022\022\n\014dberr_db"
    "data\020\263\242\014\022\023\n\rdberr_netsend\020\264\242\014\022\023\n\rdberr_n"
    "etrecv\020\265\242\014\022\025\n\017dberr_keyexists\020\266\242\014\022\027\n\021dbe"
    "rr_keynotfound\020\267\242\014\022\024\n\016dberr_noupdate\020\270\242\014"
    "\022\027\n\021dberr_net_timeout\020\271\242\014\022\027\n\021dberr_flowc"
    "ontrol\020\272\242\014\022\017\n\tdberr_md5\020\275\242\014\022\024\n\016dberr_pas"
    "sword\020\217\243\014\022\025\n\017dberr_uidexists\020\220\243\014\022\026\n\020dber"
    "r_uidnofound\020\221\243\014\022\031\n\023dberr_role_notfound\020"
    "\321\350\014\022\027\n\021dberr_role_exists\020\322\350\014\022\036\n\030dberr_cr"
    "trole_time_limit\020\323\350\014\022\037\n\031dberr_duplicated"
    "_nickname\020\324\350\014", 1573);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "errcode.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_errcode_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_errcode_2eproto {
  StaticDescriptorInitializer_errcode_2eproto() {
    protobuf_AddDesc_errcode_2eproto();
  }
} static_descriptor_initializer_errcode_2eproto_;
const ::google::protobuf::EnumDescriptor* ol_errcode_t_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ol_errcode_t_descriptor_;
}
bool ol_errcode_t_IsValid(int value) {
  switch(value) {
    case 100001:
    case 100002:
    case 100003:
    case 110001:
    case 110002:
    case 110003:
    case 110004:
    case 110005:
    case 110006:
    case 110007:
    case 110008:
    case 110009:
    case 110010:
    case 120010:
    case 120011:
    case 120012:
    case 120013:
    case 120014:
    case 120015:
    case 120016:
    case 120017:
    case 120018:
    case 120019:
    case 120020:
    case 120021:
    case 120022:
    case 120023:
    case 120030:
    case 120031:
    case 120032:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* db_errcode_t_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return db_errcode_t_descriptor_;
}
bool db_errcode_t_IsValid(int value) {
  switch(value) {
    case 0:
    case 201001:
    case 201002:
    case 201003:
    case 201004:
    case 201005:
    case 201006:
    case 201007:
    case 201008:
    case 201009:
    case 201010:
    case 201011:
    case 201012:
    case 201013:
    case 201014:
    case 201015:
    case 201016:
    case 201017:
    case 201018:
    case 201021:
    case 201103:
    case 201104:
    case 201105:
    case 210001:
    case 210002:
    case 210003:
    case 210004:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
