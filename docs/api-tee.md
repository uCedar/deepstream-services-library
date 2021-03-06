# Demuxer and Splitter - Tee API

#### Tee Construction and Destruction
Demuxers and Splitters are created using a type specific constructor,  [dsl_tee_demuxer_new](#dsl_tee_demuxer_new) and [dsl_tee_splitter_new](#dsl_tee_splitter_new) respectively

Pipelines use Tees to create Branches and Branches can use Tees to create more Branches. Therefore, Tees are added to Pipelines and Branches, while Branches are added to Tees.

The relationship between Pipline/Branch and Tee is one to one with the Tee becoming the end component. The relationshipe between Tees and Branches is one-to-many. Once added to a Pipeline or Branch, a Tee must be removed before it can used with another. 

Tees and Branches are deleted by calling [dsl_component_delete](api-component.md#dsl_component_delete), [dsl_component_delete_many](api-component.md#dsl_component_delete_many), or [dsl_component_delete_all](api-component.md#dsl_component_delete_all)

#### Adding and removing Branches from a Tee
Branches are added to a Tee by calling [dsl_tee_branch_add](api-branch.md#dsl_tee_branch_add) or [dsl_tee_branch_add_many](api-branch.md#dsl_tee_branch_add_many) and removed with [dsl_tee_branch_remove](api-branch.md#dsl_tee_branch_remove), [dsl_tee_branch_remove_many](api-branch.md#dsl_tee_branch_remove_many), or [dsl_tee_branch_remove_all](api-branch.md#dsl_tee_branch_remove_all).

## Tee API
**Constructors**
* [dsl_tee_demuxer_new](#dsl_tee_demuxer_new)
* [dsl_tee_splitter_new](#dsl_tee_splitter_new) 

**Methods**
* [dsl_tee_branch_add](#dsl_tee_branch_add)
* [dsl_tee_branch_add_many](#dsl_tee_branch_add_many)
* [dsl_tee_branch_remove](#dsl_tee_branch_remove)
* [dsl_tee_branch_remove_many](#dsl_tee_branch_remove_many)
* [dsl_tee_branch_remove_all](#dsl_tee_branch_remove_all).
* [dsl_tee_branch_count_get](#dsl_tee_branch_count_get).
* [dsl_tee_batch_meta_handler_add](#dsl_tee_batch_meta_handler_add).
* [dsl_tee_batch_meta_handler_remove](#dsl_tee_batch_meta_handler_remove).

## Return Values
The following return codes are used by the Tiler API
```C++
#define DSL_RESULT_TEE_RESULT                                       0x000A0000
#define DSL_RESULT_TEE_NAME_NOT_UNIQUE                              0x000A0001
#define DSL_RESULT_TEE_NAME_NOT_FOUND                               0x000A0002
#define DSL_RESULT_TEE_NAME_BAD_FORMAT                              0x000A0003
#define DSL_RESULT_TEE_THREW_EXCEPTION                              0x000A0004
#define DSL_RESULT_TEE_BRANCH_IS_NOT_CHILD                          0x000A0005
#define DSL_RESULT_TEE_BRANCH_ADD_FAILED                            0x000A0006
#define DSL_RESULT_TEE_BRANCH_REMOVE_FAILED                         0x000A0007
#define DSL_RESULT_TEE_HANDLER_ADD_FAILED                           0x000A0008
#define DSL_RESULT_TEE_HANDLER_REMOVE_FAILED                        0x000A0009
#define DSL_RESULT_TEE_COMPONENT_IS_NOT_TEE                         0x000A000A
```

## Constructors

### *dsl_tee_demuxer_new*
```C++
DslReturnType dsl_tee_demuxer_new(const wchar_t* name);
```
The constructor creates a uniquely named Demuxer Tee. Construction will fail if the name is currently in use. 

**Parameters**
* `name` - [in] unique name for the Demuxer to create.

**Returns**
* `DSL_RESULT_SUCCESS` on successful creation. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
retval = dsl_tee_demuxer_new('my-demuxer')
```

<br>

### *dsl_tee_splitter_new*
```C++
DslReturnType dsl_tee_splitter_new(const wchar_t* name);
```
The constructor creates a uniquely named Splitter Tee. Construction will fail if the name is currently in use. 

**Parameters**
* `name` - [in] unique name for the Splitter to create.

**Returns**
* `DSL_RESULT_SUCCESS` on successful creation. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
retval = dsl_tee_splitter_new('my-demuxer')
```

<br>

## Methods
### *dsl_tee_branch_add*
```C++
DslReturnType dsl_tee_branch_add(const wchar_t* branch, const wchar_t* component);
```
Adds a single named Component to a named Branch. The add service will fail if the component is currently `in-use` by any Branch. The add service will also fail if adding a `one-only` type of Component, such as a Tiled-Display, for which the Branch already has. The Component's `in-use` state will be set to `true` on successful add. 

If a Branch is in a `playing` or `paused` state, the service will attempt a dynamic update if possible, returning from the call with the Branch in the same state.

**Parameters**
* `branch` - [in] unique name for the Branch to update.
* `component` - [in] unique name of the Component to add.

**Returns**
* `DSL_RESULT_SUCCESS` on successful add. One of the [Return Values](#return-values) defined above on failure

**Python Example**
```Python
retval = dsl_source_csi_new('my-camera-source', 1280, 720, 30, 1)
retval = dsl_branch_new('my-branch')

retval = dsl_tee_branch_add('my-branch', 'my-tiler’)
```

<br>

### *dsl_tee_branch_add_many*
```C++
DslReturnType dsl_tee_branch_add_many(const wchar_t* branch, const wchar_t** components);
```
Adds a list of named Component to a named Branch. The add service will fail if any of components are currently `in-use` by any Branch. The add service will fail if any of the components to add are a `one-only` type of component for which the Branch already has. All the component's `in-use` states will be set to true on successful add. 

If a Branch is in a `playing` or `paused` state, the service will attempt a dynamic update if possible, returning from the call with the Branch in the same state.

**Parameters**
* `branch` - [in] unique name for the Branch to update.
* `components` - [in] a NULL terminated array of uniquely named Components to add.

**Returns**
* `DSL_RESULT_SUCCESS` on successful add. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
retval = dsl_tee_branch_add_many('my-branch', ['my-pgie', 'my-tiler', 'my-window-sink', None])
```

<br>

### *dsl_branch_componen_count_get*
```C++
uint dsl_branch_list_size(wchar_t* branch);
```
This method returns the size of the current list of Components `in-use` by the named Branch

**Parameters**
* `branch` - [in] unique name for the Branch to query.

**Returns** 
* The size of the list of Components currently in use

<br>

### *dsl_tee_branch_remove*
```C++
DslReturnType dsl_tee_branch_remove(const wchar_t* branch, const wchar_t* component);
```
Removes a single named Component from a named Branch. The remove service will fail if the Component is not currently `in-use` by the Branch. The Component's `in-use` state will be set to `false` on successful removal. 

If a Branch is in a `playing` or `paused` state, the service will attempt a dynamic update if possible, returning from the call with the Branch in the same state.

**Parameters**
* `branch` - [in] unique name for the Branch to update.
* `component` - [in] unique name of the Component to remove.

**Returns**
* `DSL_RESULT_SUCCESS` on successful add. One of the [Return Values](#return-values) defined above on failure

**Python Example**
```Python
retval = dsl_tee_branch_remove('my-branch', 'my-tiler')
```
<br>

### *dsl_tee_branch_remove_many*
```C++
DslReturnType dsl_tee_branch_remove_many(const wchar_t* branch, const wchar_t** components);
```
Removes a list of named components from a named Branch. The remove service will fail if any of components are currently `not-in-use` by the named Branch.  All of the removed component's `in-use` state will be set to `false` on successful removal. 

If a Branch is in a `playing` or `paused` state, the service will attempt a dynamic update if possible, returning from the call with the Branch in the same state.

**Parameters**
* `branch` - [in] unique name for the Branch to update.
* `components` - [in] a NULL terminated array of uniquely named Components to add.

**Returns**
* `DSL_RESULT_SUCCESS` on successful add. One of the [Return Values](#return-values) defined above on failure

**Python Example**
```Python
retval = dsl_tee_branch_remove_many('my-branch', ['my-pgie', 'my-tiler', 'my-window-sink', None])
```

<br>

### *dsl_tee_branch_remove_all*
```C++
DslReturnType dsl_tee_branch_add_(const wchar_t* branch);
```
Removes all child components from a named Branch. The add service will fail if any of components are currently `not-in-use` by the named Branch.  All the removed component's `in-use` state will be set to `false` on successful removal. 

**Parameters**
* `branch` - [in] unique name for the Branch to update.

**Returns**
* `DSL_RESULT_SUCCESS` on successful add. One of the [Return Values](#return-values) defined above on failure

**Python Example**
```Python
retval = dsl_tee_branch_remove_all('my-branch')
```


### *dsl_tee_batch_meta_handler_add*
```C++
DslReturnType dsl_tee_batch_meta_handler_add(const wchar_t* name,
    dsl_batch_meta_handler_cb handler, void* user_data);
```
This function adds a batch meta handler callback function of type [dsl_batch_meta_handler_cb](#dsl_batch_meta_handler_cb) to the `sink-pad`, on the single input to the Tee (Demuxer or Splitter). Once added, the handler will be called to handle batch-meta data for each frame buffer. A Tee can have more than one `sink-pad` (only) batch meta handler, and each handler can be added to more than one Tee.

**Parameters**
* `name` - [in] unique name of the Demuxer or Splitter to update.
* `handler` - [in] callback function to process batch meta data
* `user_data` [in] opaque pointer to the the caller's user data - passed back with each callback call.

**Returns**
* `DSL_RESULT_SUCCESS` on successful update. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
##
# Create a new Demuxer and add the batch-meta handler function.
#
retval = dsl_tee_demuxer_new('my-demuxer')
retval += dsl_tee_batch_meta_handler_add('my-demuxer', my_batch_meta_handler_cb, None)

if retval != DSL_RESULT_SUCCESS:
    # Demuxer setup failed
```    

<br>

### *dsl_tee_batch_meta_handler_remove*
```C++
DslReturnType dsl_tee_batch_meta_handler_remove(const wchar_t* name, 
    dsl_batch_meta_handler_cb handler, void* user_data);
```
This function removes a batch meta handler callback function of type [dsl_batch_meta_handler_cb](#dsl_batch_meta_handler_cb), previously added to the Tee with [dsl_tee_batch_meta_handler_add](#dsl_tee_batch_meta_handler_add). A Tee can have more than one Sink batch meta handler, and each handler can be added to more than one Tiler. Each callback added to a single pad must be unique.

**Parameters**
* `name` - [in] unique name of the Demuxer of Splitter to update.
* `handler` - [in] callback function to remove

**Returns**
*`DSL_RESULT_SUCCESS` on successful update. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
    retval = dsl_tee_batch_meta_handler_remove('my-demuxer', my_batch_meta_handler_cb)
```

<br>

---

## API Reference
* [List of all Services](/docs/api-reference-list.md)
* [Pipeline](/docs/api-pipeline.md)
* [Source](/docs/api-source.md)
* [Dewarper](/docs/api-dewarper.md)
* [Primary and Secondary GIE](/docs/api-gie.md)
* [Tracker](/docs/api-tracker.md)
* [On-Screen Display](/docs/api-osd.md)
* [Sink](/docs/api-sink.md)
* **Demuxer and Splitter**
* [Branch](/docs/api-branch.md)
* [Component](/docs/api-component.md)
