/*
 * Created by loghin on 04/03/23.
 */

#ifndef __C_ENG_ENG_PREPRO_H__
#define __C_ENG_ENG_PREPRO_H__


#define __ENG_CONCATS2(_l, _r) _l ## _r
#define __ENG_CONCAT(_l, _r) __ENG_CONCATS2(_l, _r)

#define __ENG_HANDLE(_t) struct __ENG_CONCAT(__ENG_CONCAT(__, _t), Private)
#define __ENG_DEFINE_HANDLE(_t) typedef __ENG_HANDLE(_t) * _t


#endif /* __C_ENG_ENG_PREPRO_H__ */
