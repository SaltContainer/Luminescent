#include "PlayerWork.hpp"
#include "Dpr/Nx/SaveSystem.hpp"

#include <cstdlib>
#include <cstdio>
#include "logger.hpp"
#include "Save.hpp"
#include "util.hpp"
#include "System/String.hpp"
#include "il2cpp.hpp"
#include "nn/fs.h"
#include "Dpr/Nx/SaveSystem.hpp"

extern System::String * StringLiteral_10006;
extern System::String * StringLiteral_10007;
extern System::String * StringLiteral_10008;


bool PlayerWork_CustomSaveAsyncOperation_Reroute(PlayerWork *this_, MethodInfo *method)
{
  this_->CustomSaveOperation((MethodInfo *) nullptr);
  return true;
}

void PlayerWork_CustomSaveAsyncOperation_NewHook(PlayerWork *this_, System_Byte_array ** ptr_buf, MethodInfo * method)
{
  socket_log("PlayerWork_CustomSaveAsyncOperation_NewHook\n");
  socket_log_fmt("this_: %08X\n", this_);
  DPData::ZUKAN_WORK_o zukanWork = PlayerWork::get_zukan(nullptr, nullptr);
  System_Byte_array *data = * ptr_buf;
  uint8_t * buf = (uint8_t *) &data->m_Items;
  void * ptr = PlayerWork::get_tr_battleData()->m_Items;
  socket_log_fmt("ptr: %08X\n", ptr);
  uint32_t version = 0xFFFF0000 | 0x0100 | 0x34; // Rev 1 Lumi Save
  memcpy(&buf[0], &version, sizeof(uint32_t));
  memcpy(&buf[0x7D3E0], ptr, 0x586); // 0x1618
  // Pokedex Save Data
  memcpy(&buf[0x7A328], &zukanWork.fields.get_status->m_Items, 0x1ed * sizeof(int32_t));
  memcpy(&buf[0x7aadc], &zukanWork.fields.male_color_flag->m_Items, 0x1ed); 
  memcpy(&buf[0x7acc9], &zukanWork.fields.female_color_flag->m_Items, 0x1ed);
  memcpy(&buf[0x7aeb6], &zukanWork.fields.male_flag->m_Items, 0x1ed); 
  memcpy(&buf[0x7b0a3], &zukanWork.fields.female_flag->m_Items, 0x1ed);
  return;
}

bool Dpr_NX_SaveSystem_Save(System_Byte_array *data, bool writeMain, bool writeBackup, MethodInfo * method)
{
  socket_log("Dpr_NX_SaveSystem_Save\n");

  bool success;
  nn::fs::FileHandle fileHandle;
  nn::Result result[2];
  
  system_load_typeinfo((void *)0x757e);
  
  result[0].value = 0;
  fileHandle.handle = 0;

  il2cpp_runtime_class_init(Dpr::Nx::SaveSystem_TypeInfo);

  socket_log("Mounting...\n");

  Dpr::Nx::SaveSystem::MountSaveData((MethodInfo *) nullptr);
  fileHandle.handle = 0;

  socket_log("Hitting the if...\n");

  if (writeMain) {
    socket_log("Deleting SaveData...\n");
    nn::fs::DeleteFile("SaveData:/SaveData.bin");
    socket_log("Creating SaveData...\n");
    result[0] = nn::fs::CreateFile("SaveData:/SaveData.bin",(s64)*(&data->max_length));
    if (result[0].isSuccess()) {
      socket_log("Writing SaveData...\n");
      socket_log("  Opening SaveData...\n");
      nn::fs::OpenFile(&fileHandle,"SaveData:/SaveData.bin",2);
      socket_log("  Writing SaveData...\n");
      nn::fs::WriteFile(fileHandle,0,data,(s64)*(&data->max_length),nn::fs::WriteOption(1));
      socket_log("  Closing SaveData...\n");
      nn::fs::CloseFile(fileHandle);
      if (writeBackup) {
        socket_log("Deleting Backup...\n");
        nn::fs::DeleteFile("SaveData:/Backup.bin");
        socket_log("Creating Backup...\n");
        result[0] = nn::fs::CreateFile("SaveData:/Backup.bin",(s64)*(&data->max_length));
        if (!result[0].isSuccess()) return false;
        socket_log("Writing Backup...\n");
        socket_log("  Opening Backup...\n");
        nn::fs::OpenFile(&fileHandle,"SaveData:/Backup.bin",2);
        socket_log("  Writing Backup...\n");
        nn::fs::WriteFile(fileHandle,0,data,(s64)*(&data->max_length),nn::fs::WriteOption(1));
        socket_log("  Closing Backup...\n");
        nn::fs::CloseFile(fileHandle);
      }
      socket_log("Commiting changes...\n");
      result[0] = nn::fs::CommitFileSystem("SaveData");
      success = result[0].isSuccess();
    }
  }
  else
  {
    if (writeBackup) {
      socket_log("Deleting Backup...\n");
      nn::fs::DeleteFile("SaveData:/Backup.bin");
      socket_log("Creating Backup...\n");
      result[0] = nn::fs::CreateFile("SaveData:/Backup.bin", (s64)*(&data->max_length));
      if (!result[0].isSuccess()) return false;
      socket_log("Writing Backup...\n");
      nn::fs::OpenFile(&fileHandle,"SaveData:/Backup.bin",2);
      nn::fs::WriteFile(fileHandle,0,data,(s64)*(&data->max_length),1);
      nn::fs::CloseFile(fileHandle);
    }
    socket_log("Commiting changes...\n");
    result[0] = nn::fs::CommitFileSystem("SaveData");
    success = result[0].isSuccess();
  }

  socket_log("Returning...\n");
  return success;
}