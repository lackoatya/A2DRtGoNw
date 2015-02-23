#pragma once

namespace Engine
{
	namespace Core
	{
		template < class ResultType >
		class ProcessResult
		{
		public:
			inline ProcessResult(void) = delete;
			inline ProcessResult(ResultType const& _result) : result(_result) { }
			inline ProcessResult(ProcessResult && _other) : result(_other.result) { }
			inline ProcessResult(ProcessResult const& _other) : result(_other.result) { }
			inline ProcessResult & operator=(ProcessResult const& _other) { result = _other.result; return *this; }
			inline virtual ~ProcessResult(void) = default;

			inline ResultType const& Value(void) const { return result; }

			virtual bool Valid(void) const = 0;

		protected:
			ResultType result;
		};
	}
}