/*! 
*  \file	  inifile.h
*  \brief     IniFile 头文件
*  \details   IniFile 头文件，包含IniFile类的定义，用于管理ini文件
*  \author    陈小伟 
*  \version   1.1
*  \date      2012-7-18
*  \bug       报告BUG，请联系 cxwtc123@gmail.com
*  \copyright free
*/

#ifndef CXW_INIFILE_H
#define CXW_INIFILE_H

#include <map>

//!  CXW命名空间 
/*!
CXW的C++命名空间
*/
namespace CXW {

	//!  Ini文件管理类. 允许对Ini文件内容进行读写
	/*!
	1.每个对象对应一个默认文件，构造 和 Read操作 将更改默认文件名称\n
	2.对于一个配置项而言，Section不是必须的\n
	3.配置类别可以重复\n
	4.重复的配置项会被忽略\n
	*/
	class IniFile {

	public:

		IniFile( const std::string & filename = "" );
		~IniFile();

		/**
		* @brief 清空内容
		*
		* Clear()清空内容
		*
		* @return 空
		*/
		void Clear();

		/**
		* @brief 读取文件内容
		*
		* Read()读取文件内容
		*
		* @return 空
		*/
		void Read( 
			const std::string & filename	/**< [in] 文件名 */
			);

		/**
		* @brief 保存配置信息到文件
		*
		* Save()保存配置信息到指定的文件
		*
		* @return 是否成功
		*/
		bool Save(
			const std::string & filename	/**< [in] 文件名 */
			) const;

		/**
		* @brief 保存配置信息到默认文件
		*
		* Save()保存配置信息到默认文件
		*
		* @return 是否成功
		*/
		bool Save() const;

		/**
		* @brief 获取默认文件名称
		*
		* FileName()获取默认文件名称
		*
		* @return 文件名称，可能为空
		*/
		const std::string & FileName() const;


		/**
		* @brief 增加配置项
		*
		* Add() 增加配置项，如果已存在，则修改
		*
		* @return 空
		*/
		void Add(
			const std::string & section,	/**< [in] 配置类别 */
			const std::string & name,		/**< [in] 配置名称 */
			const std::string & value		/**< [in] 配置值 */
			);

		/**
		* @brief 修改配置项
		*
		* Modify() 修改配置项，如果不存在，则无法修改
		*
		* @return 空
		*/
		void Modify( 
			const std::string & section,	/**< [in] 配置类别 */
			const std::string & name,		/**< [in] 配置名称 */
			const std::string & value		/**< [in] 配置值 */
			);

		/**
		* @brief 删除配置项
		*
		* Del() 删除配置项
		*
		* @return 空
		*/
		void Del(
			const std::string & section,	/**< [in] 配置类别 */
			const std::string & name		/**< [in] 配置名称 */
			);

		/**
		* @brief 判断配置类别是否存在
		*
		* HasSection() 判断配置类别是否存在
		*
		* @return 是否存在
		*/
		bool HasSection(
			const std::string & section		/**< [in] 配置类别 */
			) const;

		/**
		* @brief 判断配置项是否存在
		*
		* HasSetting() 判断配置项是否存在
		*
		* @return 是否存在
		*/
		bool HasSetting( 
			const std::string & section,	/**< [in] 配置类别 */
			const std::string & name		/**< [in] 配置名称 */
			) const;

		/**
		* @brief 获取配置项的值
		*
		* Value() 获取配置项的值
		*
		* @return 配置项的值
		*/
		std::string Value(
			const std::string & section,	/**< [in] 配置类别 */
			const std::string & name		/**< [in] 配置名称 */
			) const;

	private:

		struct Key {
			std::string mSection;	///<配置类别
			std::string mName;		///<配置名称

			Key( const std::string & sect, const std::string & name );
			bool operator < ( const Key & e ) const;

		};

		typedef std::map <Key,std::string> MapType;
		MapType mMap;			///<存储配置项的Map

		std::string mFileName;	///<默认文件名

	};

	//----------------------------------------------------------------------------

} // namespace


#endif