/*
 * GStreamer
 * Copyright (C) 2019 Matthew Waters <matthew@centricular.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __GST_VULKAN_COMMAND_BUFFER_H__
#define __GST_VULKAN_COMMAND_BUFFER_H__

#include <gst/gst.h>

#include <gst/vulkan/vulkan_fwd.h>
#include <gst/vulkan/gstvkapi.h>

G_BEGIN_DECLS

GST_VULKAN_API
GType gst_vulkan_command_buffer_get_type (void);
#define GST_TYPE_VULKAN_COMMAND_BUFFER (gst_vulkan_command_buffer_get_type ())

typedef struct _GstVulkanCommandBuffer GstVulkanCommandBuffer;

struct _GstVulkanCommandBuffer
{
  GstMiniObject             parent;

  VkCommandBuffer           cmd;

  /* <protected> */
  GstVulkanCommandPool     *pool;
  VkCommandBufferLevel      level;

  GMutex                    lock;
};

/**
 * gst_vulkan_command_buffer_ref: (skip)
 * @cmd: a #GstVulkanCommandBuffer.
 *
 * Increases the refcount of the given buffer by one.
 *
 * Returns: (transfer full): @buf
 */
static inline GstVulkanCommandBuffer* gst_vulkan_command_buffer_ref(GstVulkanCommandBuffer* cmd);
static inline GstVulkanCommandBuffer *
gst_vulkan_command_buffer_ref (GstVulkanCommandBuffer * cmd)
{
  return (GstVulkanCommandBuffer *) gst_mini_object_ref (GST_MINI_OBJECT_CAST (cmd));
}

/**
 * gst_vulkan_command_buffer_unref: (skip)
 * @cmd: (transfer full): a #GstVulkanCommandBuffer.
 *
 * Decreases the refcount of the buffer. If the refcount reaches 0, the buffer
 * will be freed.
 */
static inline void gst_vulkan_command_buffer_unref(GstVulkanCommandBuffer* cmd);
static inline void
gst_vulkan_command_buffer_unref (GstVulkanCommandBuffer * cmd)
{
  gst_mini_object_unref (GST_MINI_OBJECT_CAST (cmd));
}

/**
 * gst_clear_vulkan_command_buffer: (skip)
 * @cmd_ptr: a pointer to a #GstVulkanCommandBuffer reference
 *
 * Clears a reference to a #GstVulkanCommandBuffer.
 *
 * @buf_ptr must not be %NULL.
 *
 * If the reference is %NULL then this function does nothing. Otherwise, the
 * reference count of the command buffer is decreased and the pointer is set
 * to %NULL.
 *
 * Since: 1.16
 */
static inline void
gst_clear_vulkan_command_buffer (GstVulkanCommandBuffer ** cmd_ptr)
{
  gst_clear_mini_object ((GstMiniObject **) cmd_ptr);
}

#define gst_vulkan_command_buffer_lock(cmd) (gst_vulkan_command_pool_lock((cmd)->pool))
#define gst_vulkan_command_buffer_unlock(cmd) (gst_vulkan_command_pool_unlock((cmd)->pool))

GST_VULKAN_API
GstVulkanCommandBuffer *    gst_vulkan_command_buffer_new_wrapped       (VkCommandBuffer cmd,
                                                                         VkCommandBufferLevel level);

G_END_DECLS

#endif /* _GST_VULKAN_COMMAND_BUFFER_H_ */
