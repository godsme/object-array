
from pygments.lexers.c_cpp import CppLexer
from pygments.token import Name, Keyword
from pygments.lexers import get_lexer_by_name  # refer LEXERS
from pygments.lexers._mapping import LEXERS

class CppTransDslLexer(CppLexer):
    EXTRA_KEYWORDS = set(( 'ArrayView', 'ConstArrayView', 'ObjectArray',
                          'ScatteredArray', '__apply', '__with', '__is_failed', '__is_succ', '__not',
                          '__bind_listener', '__listeners'))
    FUNC_KEYWORDS  = set(('handleEvent', 'kill', 'WAIT_ON', 'onActionStarting', 'onActionEventConsumed'
                          'onActionDone', 'onActionStopped', 'onActionKilled'))
    TYPE_KEYWORDS  = set(('ForEach',  'MinElem',  'Slice', 'MinElemIndex', 'MinElemEx', 'Find',
                          'FindIndex', 'MaxElem', 'MaxElemIndex', 'MaxElemEx', 'MinElemIndexEx', 'MaxElemIndexEx',
                          'From', 'Until', 'Scope', 'Exclude', 'WithIndex',
                          'Sort', 'DescSort', 'SortEx', 'DescSortEx', 'SortObject', 'PartialDescSort', 'StableDescSort',
                          'PartialSort', 'StableSort', 'Exists', 'Append', 'At', 'First', 'Last',
                          'Erase', 'GetNum', 'Any', 'All', 'None', 'Replace', 'GetOccupied', 'IsPresent',
                          'Remove', 'Clear', 'ClearFrom', 'ClearUntil', 'RemoveBy', 'CleanUp', 'CleanUpEx', 'CleanUpBy'))
    CONST_KEYWORDS = set(('ASSERT', 'UNKNOWN_EVENT', 'FAILED',
                          'DEF_SIMPLE_ASYNC_ACTION'))

    def get_tokens_unprocessed(self, text):
        for index, token, value in CppLexer.get_tokens_unprocessed(self, text):
            if token is Name and value in self.EXTRA_KEYWORDS:
                yield index, Keyword, value
            elif token is Name and value in self.FUNC_KEYWORDS:
                yield index, Name.Function, value
            elif token is Name and value in self.TYPE_KEYWORDS:
                yield index, Name.Class, value
            elif token is Name and value in self.CONST_KEYWORDS:
                yield index, Name.Constant, value
            else:
                yield index, token, value


def setup(app):
    app.add_lexer('c++', CppTransDslLexer)
