#include "Animation.hpp"


Animation::Animation(std::string const& name,
                     std::vector<unsigned int> delaysMs)
  : spriteSet(Resources::getTexture(name))
{
  char readBuffer[65536];
  std::string propertyPath = Resources::getPath(name + "_properties");
  FILE* propertyFile = fopen(propertyPath.c_str(), "r");
  rapidjson::FileReadStream propertyStream(propertyFile, readBuffer, sizeof(readBuffer));

  rapidjson::Document doc;
  doc.ParseStream(propertyStream);
  fclose(propertyFile);

  if (doc.HasParseError()) {
    throw; // @todo
  }

  unsigned int nFrames = doc["nFrames"].GetUint();
  size = {
    (spriteSet.getSize().x - nFrames + 1) / nFrames,
    spriteSet.getSize().y
  };
  frames.reserve(nFrames);
  for (unsigned int i = 0; i < nFrames; ++i) {
    unsigned int delay;
    if (i < frames.size()) {
      delay = delaysMs[i];
    }
    else {
      delay = delaysMs[delaysMs.size() - 1];
    }
    frames.push_back({
      delay,
      {
        static_cast<int>(i * (size.x + 1)),
        0,
        static_cast<int>(size.x),
        static_cast<int>(size.y)
      }
    });
  }

  currentSprite.setTexture(spriteSet);
  currentSprite.setTextureRect(frames[0].textureRectangle);
}


void Animation::update(sf::Time time) {
  if (frames[currentFrame].delayMs == 0 ||
      iteration >= nIterations) {
    return;
  }
  timeSinceFrameChangeMs += time.asMilliseconds();
  if (timeSinceFrameChangeMs > frames[currentFrame].delayMs) {
    ++currentFrame;
    if (currentFrame == frames.size()) {
      currentFrame = 0;
      ++iteration;
    }
    currentSprite.setTextureRect(frames[currentFrame].textureRectangle);
    timeSinceFrameChangeMs = 0;
  }
}


void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (iteration >= nIterations) {
    return;
  }
  target.draw(currentSprite, states);
}


void Animation::setPosition(sf::Vector2f pos, bool isCentered) {
  if (isCentered) {
    auto b = currentSprite.getLocalBounds();
    currentSprite.setOrigin(b.width / 2, b.height / 2);
  }
  currentSprite.setPosition(pos);
}


void Animation::setHeight(float height) {
  float scale = (float)height / size.y;
  currentSprite.setScale(scale, scale);
}


void Animation::flipHorizontal(bool flipped) {
  bool isFlipped = frames[0].textureRectangle.width < 0 ? true : false;
  if (flipped == isFlipped) {
    return;
  }

  for (auto& frame: frames) {
    auto& r = frame.textureRectangle;
    r.left = r.left + r.width;
    r.width = -r.width;
  }
  currentSprite.setTextureRect(frames[currentFrame].textureRectangle);
}


void Animation::setIterations(unsigned int nIterations) {
  this->nIterations = nIterations;
}


sf::Vector2f Animation::getSize() const {
  return {
    size.x * currentSprite.getScale().x,
    size.y * currentSprite.getScale().y
  };
}
