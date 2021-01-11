import re
import string
import sys


class VerifierReader(object):
  def __init__(self, text):
    self.text = text
    self.position = 0

  def HasNext(self):
    return self.position < len(self.text)

  def Read(self, target):
    actual = self.text[self.position : self.position + len(target)]
    assert actual == target, "Could not read '{0}'".format(target)
    self.position += len(target)

  def ReadEndl(self):
    self.Read('\n')

  def ReadEof(self):
    assert self.position == len(self.text), 'Found junk at the end of the file'

  def ReadChar(self):
    assert self.position < len(self.text), 'Unexpected EOF'
    char = self.text[self.position]
    self.position += 1
    return char

  def ReadLine(self, valid_characters):
    old_position = self.position
    while True:
      assert self.position < len(self.text), 'Unexpected EOF'
      c = self.text[self.position]
      self.position += 1
      if c == '\n':
        break
      assert c in valid_characters
    assert self.position - old_position > 1, 'Nothing before next newline'
    return self.text[old_position:self.position - 1]

  def ReadRegex(self, target_regex):
    match = re.compile(target_regex).match(self.text, self.position)
    assert match is not None, 'Could not match /%s/' % target_regex
    self.position = match.end()
    return match.group(0)

  def ReadList(self, n, read_fn, *args):
    ls = []
    for i in range(n):
      if i > 0:
        self.Read(' ')
      ls.append(read_fn())
    self.ReadEndl()
    return ls

  def ReadInt(self, inclusive_min, inclusive_max):
    value = int(self.ReadRegex(r'0|(-?[1-9][0-9]*)'))
    assert inclusive_min <= value <= inclusive_max, (
        'Failed on %d <= %d <= %d' % (inclusive_min, value, inclusive_max))
    return value

  def ReadIntList(self, n, inclusive_min, inclusive_max):
    return self.ReadList(n, lambda: self.ReadInt(inclusive_min, inclusive_max))

  def ReadString(self, valid_characters=string.ascii_letters + string.digits,
                 inc_min_len=1, inc_max_len=10**6):
    old_position = self.position
    while True:
      assert self.position < len(self.text), 'Unexpected EOF'
      c = self.text[self.position]
      if c not in valid_characters:
        break
      self.position += 1
    st = self.text[old_position:self.position]
    assert inc_min_len <= len(st) <= inc_max_len, (
        'Invalid string length: %d' % len(st))
    return st

  def ReadStringList(self, n,
                     valid_characters=string.ascii_letters + string.digits,
                     inc_min_len=1, inc_max_len=10**6):
    return self.ReadList(
        n,
        lambda: self.ReadString(valid_characters, inc_min_len, inc_max_len))


def main(argv):
  subtask = int(argv[1])
  assert 1 <= subtask <= 10
  vr = VerifierReader(sys.stdin.read())

  maxN = 1000000000
  maxK = 100000

  N = vr.ReadInt(1, maxN)
  assert vr.ReadChar() == ' ', 'Input is not space separated.'
  M = vr.ReadInt(1, maxN)
  assert vr.ReadChar() == ' ', 'Input is not space separated.'
  K = vr.ReadInt(1, maxK)
  vr.ReadEndl()

  A = vr.ReadIntList(K, 1, 100 if subtask == 10 else maxN)
  assert sum(A) == N * M, 'Total area is not equal to NxM.'

  if subtask == 1:
    assert N == 5 and M == 5 and K == 5 and \
           A == [4, 4, 4, 4, 9], \
           'Input does not satisfy subtask 1.'

  if subtask == 2:
    assert N == 6 and M == 7 and K == 8 and \
           A == [2, 3, 4, 5, 6, 6, 7, 9],\
           'Input does not satisfy subtask 2.'

  if subtask == 3:
    assert N == 1, 'N is not equal to 1.'
    assert M == 10**9, 'M is not equal to 1000000000.'
    assert K == 10**5, 'K is not equal to 100000.'

  if subtask == 4:
    assert K == N, 'K is not equal to N.'
    for i in range(K):
      assert A[i] == i + 1, (
          'Rectangle {} does not satisfy the constraint.'.format(i + 1))

  if subtask == 5:
    for i in range(K):
      assert A[i] == N * M / K, (
          'Rectangle {} does not satisfy the constraint.'.format(i + 1))

  if subtask == 6:
    assert N == 2, 'N is not equal to 2.'
    assert M == 10**9, 'M is not equal to 1000000000.'
    assert K == 20, 'K is not equal to 20.'
    assert sum([a % 2 for a in A]) == 10, 'Unbalanced parity.'

  if subtask == 7:
    assert N == 2, 'N is not equal to 2.'
    assert M == 10000, 'M is not equal to 10000.'
    assert K == 100, 'K is not equal to 100.'

  if subtask == 8:
    assert N == 4681, 'N is not equal to 4681.'
    assert M == 229383, 'M is not equal to 229383.'
    assert K == 30, 'K is not equal to 30.'
    for i in range(K):
      assert A[i] == 2 ** i, (
          'Rectangle {} does not satisfy the constraint.'.format(i + 1))

  if subtask == 9:
    assert N == 46368, 'N is not equal to 46368.'
    assert M == 28657, 'M is not equal to 28657.'
    assert K == 23, 'K is not equal to 23.'
    a = 0
    b = 1
    for i in range(K):
      a, b = b, a + b
      assert A[i] == a * a, (
          'Rectangle {} does not satisfy the constraint.'.format(i + 1))

  vr.ReadEof()


if __name__ == '__main__':
  sys.exit(main(sys.argv))
