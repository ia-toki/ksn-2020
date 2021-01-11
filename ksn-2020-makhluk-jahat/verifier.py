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
  assert 1 <= subtask <= 9
  vr = VerifierReader(sys.stdin.read())

  maxN = 200000
  minK, maxK = 4, 20
  maxLibrary = 100

  if subtask == 3:
    maxLibrary = 0

  if subtask == 4:
    maxLibrary = 3

  if subtask == 5:
    minK, maxK = 5, 5

  if subtask == 6:
    maxN = 1000
    maxK = 10

  if subtask == 7:
    maxN = 1000
    
  if subtask == 8:
    maxK = 10

  N = vr.ReadInt(1, maxN)
  assert vr.ReadChar() == ' ', 'Input is not space separated.'
  K = vr.ReadInt(minK, maxK)
  vr.ReadEndl()

  S = vr.ReadIntList(4, 1, maxK)
  assert len(set(S)) == 4, 'Input S is not distinct.'

  M = []
  for _ in range(K):
    M.append(vr.ReadString('01', K, K))
    vr.ReadEndl()

  library, rooms = 0, []
  for _ in range(N):
    rooms.append([vr.ReadInt(1, 2)])

    if rooms[-1][0] == 1:
      assert vr.ReadChar() == ' ', 'Input is not space separated.'
      rooms[-1].append(vr.ReadInt(1, K))
    elif rooms[-1][0] == 2:
      library += 1

    vr.ReadEndl()
  vr.ReadEof()

  assert library <= maxLibrary, 'Too many rooms with library type.'

  if subtask == 1:
    assert N == 9 and K == 6 and S == [4, 6, 1, 2] and \
           M == ['000010', '100000', '000001', '001000', '010000', '000100'] and \
           rooms == [[1, 4], [1, 3], [2], [1, 6], [1, 2], [2], [1, 1,], [1, 5], [2]], \
           'Input does not satisfy subtask 1.'

  if subtask == 2:
    assert N == 24 and K == 8 and S == [5, 1, 7, 2] and \
           M == ['00100000', '00010101', '01100000', '01001110', \
                 '11000100', '10110101', '10001000', '01001100'] and \
           rooms == [[1, 7], [1, 2], [1, 7], [1, 4], [2], [1, 5], [1, 3], [1, 5], [2], [1, 2], [1, 6], [2], \
                     [1, 2], [1, 4], [1, 1], [1, 3], [1, 6], [1, 4], [1, 1], [1, 3], [1, 7], [1, 2], [1, 8], [1, 4]], \
           'Input does not satisfy subtask 2.'

if __name__ == '__main__':
  sys.exit(main(sys.argv))